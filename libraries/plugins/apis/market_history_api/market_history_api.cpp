#include <clout/plugins/market_history_api/market_history_api_plugin.hpp>
#include <clout/plugins/market_history_api/market_history_api.hpp>

#include <clout/chain/clout_objects.hpp>

#define ASSET_TO_REAL( asset ) (double)( asset.amount.value )

namespace clout { namespace plugins { namespace market_history {

namespace detail {

using namespace clout::plugins::market_history;

class market_history_api_impl
{
   public:
      market_history_api_impl() : _db( appbase::app().get_plugin< clout::plugins::chain::chain_plugin >().db() ) {}

      DECLARE_API_IMPL(
         (get_ticker)
         (get_volume)
         (get_order_book)
         (get_trade_history)
         (get_recent_trades)
         (get_market_history)
         (get_market_history_buckets)
      )

      chain::database& _db;
};

DEFINE_API_IMPL( market_history_api_impl, get_ticker )
{
   get_ticker_return result;

   const auto& bucket_idx = _db.get_index< bucket_index, by_bucket >();
   auto itr = bucket_idx.lower_bound( boost::make_tuple( args.market, 0, _db.head_block_time() - 86400 ) );

   if( itr != bucket_idx.end() )
   {
      auto open = ASSET_TO_REAL( asset( itr->non_clout.open, args.market ) ) / ASSET_TO_REAL( asset( itr->clout.open, CLOUT_SYMBOL ) );
      itr = bucket_idx.lower_bound( boost::make_tuple( args.market, 0, _db.head_block_time() ) );
      result.latest = ASSET_TO_REAL( asset( itr->non_clout.close, args.market ) ) / ASSET_TO_REAL( asset( itr->clout.close, CLOUT_SYMBOL ) );
      result.percent_change = ( (result.latest - open ) / open ) * 100;
   }

   auto orders = get_order_book( get_order_book_args{ args.market, 1 } );
   if( orders.bids.empty() == false )
      result.highest_bid = orders.bids[0].real_price;
   if( orders.asks.empty() == false )
      result.lowest_ask = orders.asks[0].real_price;


   auto volume = get_volume( { args.market } );
   result.clout_volume = volume.clout_volume;
   result.cbd_volume = volume.cbd_volume;

   return result;
}

DEFINE_API_IMPL( market_history_api_impl, get_volume )
{
   const auto& tracked_buckets = appbase::app().get_plugin< clout::plugins::market_history::market_history_plugin >().get_tracked_buckets();
   const auto& bucket_idx = _db.get_index< bucket_index, by_bucket >();

   get_volume_return result;
   fc::time_point_sec earliest_time = _db.head_block_time();
   fc::time_point_sec latest_time = _db.head_block_time() - 86400;

   for( const auto bucket_size : tracked_buckets )
   {
      auto itr = bucket_idx.lower_bound( boost::make_tuple( args.market, bucket_size, latest_time ) );

      while( itr != bucket_idx.end()
         && itr->symbol == args.market
         && itr->seconds == bucket_size )
      {
         result.clout_volume.amount += itr->clout.volume;
         result.cbd_volume.amount += itr->non_clout.volume;
         if( itr->open < latest_time ) latest_time = itr->open;
         if( itr->open > earliest_time ) earliest_time = itr->open;

         ++itr;
      }

      itr = bucket_idx.lower_bound( boost::make_tuple( args.market, bucket_size, earliest_time ) );

      while( itr != bucket_idx.end()
         && itr->open < earliest_time
         && itr->symbol == args.market
         && itr->seconds == bucket_size )
      {
         result.clout_volume.amount += itr->clout.volume;
         result.cbd_volume.amount += itr->non_clout.volume;
         if( itr->open > earliest_time ) earliest_time = itr->open;

         ++itr;
      }
   }

   return result;
}

DEFINE_API_IMPL( market_history_api_impl, get_order_book )
{
   FC_ASSERT( args.limit <= 500 );

   const auto& order_idx = _db.get_index< chain::limit_order_index, chain::by_price >();
   auto itr = order_idx.lower_bound( price::max( args.market, CLOUT_SYMBOL ) );

   get_order_book_return result;

   while( itr != order_idx.end() && itr->sell_price.base.symbol == args.market && result.bids.size() < args.limit )
   {
      order cur;
      cur.order_price = itr->sell_price;
      cur.real_price = ASSET_TO_REAL( itr->sell_price.base ) / ASSET_TO_REAL( itr->sell_price.quote );
      cur.clout = ( asset( itr->for_sale, args.market ) * itr->sell_price ).amount;
      cur.cbd = itr->for_sale;
      cur.created = itr->created;
      result.bids.push_back( cur );
      ++itr;
   }

   itr = order_idx.lower_bound( price::max( CLOUT_SYMBOL, args.market ) );

   while( itr != order_idx.end() && itr->sell_price.base.symbol == CLOUT_SYMBOL && result.asks.size() < args.limit )
   {
      order cur;
      cur.order_price = itr->sell_price;
      cur.real_price = ASSET_TO_REAL( itr->sell_price.quote ) / ASSET_TO_REAL( itr->sell_price.base );
      cur.clout = itr->for_sale;
      cur.cbd = ( asset( itr->for_sale, CLOUT_SYMBOL ) * itr->sell_price ).amount;
      cur.created = itr->created;
      result.asks.push_back( cur );
      ++itr;
   }

   return result;
}

DEFINE_API_IMPL( market_history_api_impl, get_trade_history )
{
   FC_ASSERT( args.limit <= 1000 );
   const auto& bucket_idx = _db.get_index< order_history_index, by_time >();
   auto itr = bucket_idx.lower_bound( boost::make_tuple( args.market, args.start ) );

   get_trade_history_return result;

   while( itr != bucket_idx.end() && itr->time <= args.end && result.trades.size() < args.limit )
   {
      market_trade trade;
      trade.date = itr->time;
      trade.current_pays = itr->op.current_pays;
      trade.open_pays = itr->op.open_pays;
      result.trades.push_back( trade );
      ++itr;
   }

   return result;
}

DEFINE_API_IMPL( market_history_api_impl, get_recent_trades )
{
   FC_ASSERT( args.limit <= 1000 );
   const auto& order_idx = _db.get_index< order_history_index, by_time >();
   auto itr = order_idx.upper_bound( args.market );
   auto begin = order_idx.begin();

   get_recent_trades_return result;

   if( order_idx.size() == 0 ) return result;

   do
   {
      --itr;

      if( itr->market() == args.market )
      {
         market_trade trade;
         trade.date = itr->time;
         trade.current_pays = itr->op.current_pays;
         trade.open_pays = itr->op.open_pays;
         result.trades.push_back( trade );
      }
   } while( itr != begin );

   return result;
}

DEFINE_API_IMPL( market_history_api_impl, get_market_history )
{
   const auto& bucket_idx = _db.get_index< bucket_index, by_bucket >();
   auto itr = bucket_idx.lower_bound( boost::make_tuple( args.market, args.bucket_seconds, args.start ) );

   get_market_history_return result;

   while( itr != bucket_idx.end() && itr->seconds == args.bucket_seconds && itr->open < args.end )
   {
      result.buckets.push_back( *itr );

      ++itr;
   }

   return result;
}

DEFINE_API_IMPL( market_history_api_impl, get_market_history_buckets )
{
   get_market_history_buckets_return result;
   result.bucket_sizes = appbase::app().get_plugin< clout::plugins::market_history::market_history_plugin >().get_tracked_buckets();
   return result;
}


} // detail

market_history_api::market_history_api(): my( new detail::market_history_api_impl() )
{
   JSON_RPC_REGISTER_API( CLOUT_MARKET_HISTORY_API_PLUGIN_NAME );
}

market_history_api::~market_history_api() {}

DEFINE_READ_APIS( market_history_api,
   (get_ticker)
   (get_volume)
   (get_order_book)
   (get_trade_history)
   (get_recent_trades)
   (get_market_history)
   (get_market_history_buckets)
)

} } } // clout::plugins::market_history
