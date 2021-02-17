#include <clout/plugins/chain/statefile/statefile.hpp>
#include <clout/plugins/chain/chain_plugin.hpp>

#include <clout/chain/database.hpp>
#include <clout/chain/index.hpp>

#include <appbase/application.hpp>

namespace clout { namespace plugins { namespace chain { namespace statefile {

using clout::chain::index_info;

// db_format_version : Must match CLOUT_DB_FORMAT_VERSION
// network_type      : Must match CLOUT_NETWORK_TYPE
// chain_id          : Must match requested chain ID and value of embedded GPO

clout_version_info::clout_version_info( const database& db )
{
   db_format_version = CLOUT_DB_FORMAT_VERSION;
   network_type = CLOUT_NETWORK_TYPE;
   db.for_each_index_extension< index_info >( [&]( std::shared_ptr< index_info > info )
   {
      std::shared_ptr< schema::abstract_schema > sch = info->get_schema();
      std::string schema_name, str_schema;
      sch->get_name( schema_name );
      sch->get_str_schema( str_schema );
      object_schemas.emplace( schema_name, str_schema );
   } );

   chain_id = db.get_chain_id().str();
   head_block_num = db.revision();
}

void fill_plugin_options( fc::map< std::string, fc::string >& plugin_options )
{
   for( const auto& plugin_opts : appbase::app().get_plugin< chain_plugin >().get_state_options() )
   {
      plugin_options[ plugin_opts.first ] = fc::json::to_string( plugin_opts.second );
   }
   //appbase::app().for_each_plugin( [&]( const appbase::abstract_plugin& p )
   //{
   //   boost::any opts;
   //   p.get_impacted_options( opts );
   //   if( !opts.empty() )
   //      plugin_options[ p.get_name() ] = fc::json::to_string( boost::any_cast< fc::variant_object >( opts ) );
   //});
}

} } } } // clout::plugins::chain::statefile
