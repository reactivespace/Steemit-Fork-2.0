#pragma once

#include <clout/chain/clout_fwd.hpp>
#include <clout/chain/clout_object_types.hpp>
#include <clout/protocol/smt_operations.hpp>

namespace clout { namespace chain {

using protocol::curve_id;
using protocol::smt_ticker_type;

enum class smt_phase : uint8_t
{
   setup,
   setup_completed,
   ico,
   ico_completed,
   launch_failed,
   launch_success
};

/**Note that the object represents both liquid and vesting variant of SMT.
 * The same object is returned by indices when searched by liquid/vesting symbol/nai.
 */
class smt_token_object : public object< smt_token_object_type, smt_token_object >
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( smt_token_object );

public:

   struct smt_market_maker_state
   {
      asset    clout_balance;
      asset    token_balance;
      uint32_t reserve_ratio = 0;
   };

public:

   template< typename Constructor, typename Allocator >
   smt_token_object( Constructor&& c, allocator< Allocator > a )
   {
      c( *this );
   }

   price initial_vesting_share_price() const
   {
      int64_t one_smt = std::pow( 10, liquid_symbol.decimals() );
      return
         price(
            asset( one_smt * SMT_INITIAL_VESTING_PER_UNIT, liquid_symbol.get_paired_symbol() ),
            asset( one_smt, liquid_symbol )
         );
   }

   price get_vesting_share_price() const
   {
      if ( total_vesting_fund_ballast == 0 || total_vesting_shares_ballast == 0 )
         return initial_vesting_share_price();

      share_type effective_total_vesting_shares = total_vesting_shares_ballast + total_vesting_shares;
      share_type effective_total_vesting_fund   = total_vesting_fund_ballast + total_vesting_fund_smt;

      return price( asset( effective_total_vesting_shares, liquid_symbol.get_paired_symbol() ), asset( effective_total_vesting_fund, liquid_symbol ) );
   }

   price get_reward_vesting_share_price() const
   {
      if ( total_vesting_fund_ballast == 0 || total_vesting_shares_ballast == 0 )
         return initial_vesting_share_price();

      share_type reward_vesting_shares = total_vesting_shares_ballast + total_vesting_shares + pending_rewarded_vesting_shares;
      share_type reward_vesting_smt    = total_vesting_fund_ballast + total_vesting_fund_smt + pending_rewarded_vesting_smt;

      return price( asset( reward_vesting_shares, liquid_symbol.get_paired_symbol() ), asset( reward_vesting_smt, liquid_symbol ) );
   }

   asset_symbol_type get_stripped_symbol() const
   {
      return asset_symbol_type::from_asset_num( liquid_symbol.get_stripped_precision_smt_num() );
   }

   // id_type is actually oid<smt_token_object>
   id_type              id;

   /**The object represents both liquid and vesting variant of SMT
    * To get vesting symbol, call liquid_symbol.get_paired_symbol()
    */
   asset_symbol_type    liquid_symbol;
   account_name_type    control_account;
   smt_ticker_type      desired_ticker;
   smt_phase            phase                           = smt_phase::setup;
   share_type           current_supply                  = 0;
   share_type           total_vesting_fund_smt          = 0;
   share_type           total_vesting_shares            = 0;
   share_type           total_vesting_fund_ballast      = 0;
   share_type           total_vesting_shares_ballast    = 0;
   share_type           pending_rewarded_vesting_shares = 0;
   share_type           pending_rewarded_vesting_smt    = 0;
   asset                reward_balance;

   uint128_t            recent_claims;
   time_point_sec       last_reward_update;

   time_point_sec       last_virtual_emission_time;

   smt_market_maker_state  market_maker;

   /// set_setup_parameters
   bool                 allow_voting = true;

   /// set_runtime_parameters
   uint32_t             cashout_window_seconds = CLOUT_CASHOUT_WINDOW_SECONDS;
   uint32_t             reverse_auction_window_seconds = CLOUT_REVERSE_AUCTION_WINDOW_SECONDS_HF20;

   uint32_t             vote_regeneration_period_seconds = CLOUT_VOTING_MANA_REGENERATION_SECONDS;
   uint32_t             votes_per_regeneration_period = SMT_DEFAULT_VOTES_PER_REGEN_PERIOD;

   uint128_t            content_constant = CLOUT_CONTENT_CONSTANT_HF0;
   uint16_t             percent_curation_rewards = SMT_DEFAULT_PERCENT_CURATION_REWARDS;
   protocol::curve_id   author_reward_curve = curve_id::linear;
   protocol::curve_id   curation_reward_curve = curve_id::square_root;

   bool                 allow_downvotes = true;

   ///parameters for 'smt_setup_operation'
   int64_t                       max_supply = 0;
};

class smt_ico_object : public object< smt_ico_object_type, smt_ico_object >
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( smt_ico_object );

public:
   template< typename Constructor, typename Allocator >
   smt_ico_object( Constructor&& c, allocator< Allocator > a )
   {
      c( *this );
   }

   id_type id;
   asset_symbol_type             symbol;
   time_point_sec                contribution_begin_time;
   time_point_sec                contribution_end_time;
   time_point_sec                launch_time;
   share_type                    clout_satoshi_min       = -1;
   uint32_t                      min_unit_ratio          = 0;
   uint32_t                      max_unit_ratio          = 0;
   asset                         contributed             = asset( 0, CLOUT_SYMBOL );
   share_type                    processed_contributions = 0;
};

struct shared_smt_generation_unit
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( shared_smt_generation_unit );

   template< typename Allocator >
   shared_smt_generation_unit( const Allocator& alloc ) :
      clout_unit( unit_pair_allocator_type( alloc ) ),
      token_unit( unit_pair_allocator_type( alloc ) )
   {}

   typedef chainbase::t_flat_map< clout::protocol::unit_target_type, uint16_t > unit_map_type;

   using unit_pair_allocator_type = chainbase::t_allocator_pair< clout::protocol::unit_target_type, uint16_t >;

   unit_map_type clout_unit;
   unit_map_type token_unit;

   uint32_t clout_unit_sum()const
   {
      uint32_t result = 0;
      for( const auto& e : clout_unit )
      {
         result += e.second;
      }
      return result;
   }

   uint32_t token_unit_sum()const
   {
      uint32_t result = 0;
      for( const auto& e : token_unit )
      {
         result += e.second;
      }
      return result;
   }

   shared_smt_generation_unit& operator =( const clout::protocol::smt_generation_unit& g )
   {
      clout_unit.insert( g.clout_unit.begin(), g.clout_unit.end() );
      token_unit.insert( g.token_unit.begin(), g.token_unit.end() );
      return *this;
   }

   operator clout::protocol::smt_generation_unit()const
   {
      clout::protocol::smt_generation_unit g;
      g.clout_unit.insert( clout_unit.begin(), clout_unit.end() );
      g.token_unit.insert( token_unit.begin(), token_unit.end() );
      return g;
   }
};

class smt_ico_tier_object : public object< smt_ico_tier_object_type, smt_ico_tier_object >
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( smt_ico_tier_object );

public:
   template< typename Constructor, typename Allocator >
   smt_ico_tier_object( Constructor&& c, allocator< Allocator > a )
      : generation_unit( a )
   {
      c( *this );
   }

   id_type                                id;
   asset_symbol_type                      symbol;
   share_type                             clout_satoshi_cap = -1;
   shared_smt_generation_unit             generation_unit;
};

struct shared_smt_emissions_unit
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( shared_smt_emissions_unit )

   template< typename Allocator >
   shared_smt_emissions_unit( const Allocator& alloc ) :
      token_unit( emissions_pair_allocator_type( alloc ) )
   {}

   typedef chainbase::t_flat_map< clout::protocol::unit_target_type, uint16_t > token_unit_map_type;

   using emissions_pair_allocator_type = chainbase::t_allocator_pair< public_key_type, weight_type >;

   token_unit_map_type token_unit;

   uint32_t token_unit_sum()const
   {
      uint32_t result = 0;
      for( const auto& e : token_unit )
      {
         result += e.second;
      }
      return result;
   }

   shared_smt_emissions_unit& operator =( const clout::protocol::smt_emissions_unit& u )
   {
      token_unit.insert( u.token_unit.begin(), u.token_unit.end() );
      return *this;
   }
};

class smt_token_emissions_object : public object< smt_token_emissions_object_type, smt_token_emissions_object >
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( smt_token_emissions_object );

   template< typename Constructor, typename Allocator >
   smt_token_emissions_object( Constructor&& c, allocator< Allocator > a ) :
      emissions_unit( a )
   {
      c( *this );
   }

   id_type                               id;
   asset_symbol_type                     symbol;
   time_point_sec                        schedule_time = CLOUT_GENESIS_TIME;
   shared_smt_emissions_unit             emissions_unit;
   uint32_t                              emission_count = 0;
   uint32_t                              interval_seconds = 0;
   time_point_sec                        lep_time = CLOUT_GENESIS_TIME;
   time_point_sec                        rep_time = CLOUT_GENESIS_TIME;
   share_type                            lep_abs_amount;
   share_type                            rep_abs_amount;
   uint32_t                              lep_rel_amount_numerator = 0;
   uint32_t                              rep_rel_amount_numerator = 0;
   uint8_t                               rel_amount_denom_bits = 0;

   bool                                  floor_emissions = false;

   time_point_sec schedule_end_time() const
   {
      time_point_sec end_time = time_point_sec::maximum();

      if ( emission_count != SMT_EMIT_INDEFINITELY )
         // This potential time_point overflow is protected by smt_setup_emissions_operation::validate
         end_time = schedule_time + fc::seconds( uint64_t( interval_seconds ) * uint64_t( emission_count - 1 ) );

      return end_time;
   }
};

class smt_contribution_object : public object< smt_contribution_object_type, smt_contribution_object >
{
   CLOUT_STD_ALLOCATOR_CONSTRUCTOR( smt_contribution_object );

   template< typename Constructor, typename Allocator >
   smt_contribution_object( Constructor&& c, allocator< Allocator > a )
   {
      c( *this );
   }

   id_type                               id;
   asset_symbol_type                     symbol;
   account_name_type                     contributor;
   uint32_t                              contribution_id;
   asset                                 contribution;
};

struct by_symbol_contributor;
struct by_contributor;
struct by_symbol_id;

typedef multi_index_container <
   smt_contribution_object,
   indexed_by <
      ordered_unique< tag< by_id >,
         member< smt_contribution_object, smt_contribution_object_id_type, &smt_contribution_object::id > >,
      ordered_unique< tag< by_symbol_contributor >,
         composite_key< smt_contribution_object,
            member< smt_contribution_object, asset_symbol_type, &smt_contribution_object::symbol >,
            member< smt_contribution_object, account_name_type, &smt_contribution_object::contributor >,
            member< smt_contribution_object, uint32_t, &smt_contribution_object::contribution_id >
         >
      >,
      ordered_unique< tag< by_symbol_id >,
         composite_key< smt_contribution_object,
            member< smt_contribution_object, asset_symbol_type, &smt_contribution_object::symbol >,
            member< smt_contribution_object, smt_contribution_object_id_type, &smt_contribution_object::id >
         >
      >
#ifndef IS_LOW_MEM
      ,
      ordered_unique< tag< by_contributor >,
         composite_key< smt_contribution_object,
            member< smt_contribution_object, account_name_type, &smt_contribution_object::contributor >,
            member< smt_contribution_object, asset_symbol_type, &smt_contribution_object::symbol >,
            member< smt_contribution_object, uint32_t, &smt_contribution_object::contribution_id >
         >
      >
#endif
   >,
   allocator< smt_contribution_object >
> smt_contribution_index;

struct by_symbol;
struct by_control_account;
struct by_stripped_symbol;

typedef multi_index_container <
   smt_token_object,
   indexed_by <
      ordered_unique< tag< by_id >,
         member< smt_token_object, smt_token_id_type, &smt_token_object::id > >,
      ordered_unique< tag< by_symbol >,
         member< smt_token_object, asset_symbol_type, &smt_token_object::liquid_symbol > >,
      ordered_unique< tag< by_control_account >,
         composite_key< smt_token_object,
            member< smt_token_object, account_name_type, &smt_token_object::control_account >,
            member< smt_token_object, asset_symbol_type, &smt_token_object::liquid_symbol >
         >
      >,
      ordered_unique< tag< by_stripped_symbol >,
         const_mem_fun< smt_token_object, asset_symbol_type, &smt_token_object::get_stripped_symbol > >
   >,
   allocator< smt_token_object >
> smt_token_index;

typedef multi_index_container <
   smt_ico_object,
   indexed_by <
      ordered_unique< tag< by_id >,
         member< smt_ico_object, smt_ico_object_id_type, &smt_ico_object::id > >,
      ordered_unique< tag< by_symbol >,
         member< smt_ico_object, asset_symbol_type, &smt_ico_object::symbol > >
   >,
   allocator< smt_ico_object >
> smt_ico_index;

struct by_symbol_clout_satoshi_cap;

typedef multi_index_container <
   smt_ico_tier_object,
   indexed_by <
      ordered_unique< tag< by_id >,
         member< smt_ico_tier_object, smt_ico_tier_object_id_type, &smt_ico_tier_object::id > >,
      ordered_unique< tag< by_symbol_clout_satoshi_cap >,
         composite_key< smt_ico_tier_object,
            member< smt_ico_tier_object, asset_symbol_type, &smt_ico_tier_object::symbol >,
            member< smt_ico_tier_object, share_type, &smt_ico_tier_object::clout_satoshi_cap >
         >,
         composite_key_compare< std::less< asset_symbol_type >, std::less< share_type > >
      >
   >,
   allocator< smt_ico_tier_object >
> smt_ico_tier_index;

struct by_symbol_time;
struct by_symbol_end_time;

typedef multi_index_container <
   smt_token_emissions_object,
   indexed_by <
      ordered_unique< tag< by_id >,
         member< smt_token_emissions_object, smt_token_emissions_object_id_type, &smt_token_emissions_object::id > >,
      ordered_unique< tag< by_symbol_time >,
         composite_key< smt_token_emissions_object,
            member< smt_token_emissions_object, asset_symbol_type, &smt_token_emissions_object::symbol >,
            member< smt_token_emissions_object, time_point_sec, &smt_token_emissions_object::schedule_time >
         >
      >,
      ordered_unique< tag< by_symbol_end_time >,
         composite_key< smt_token_emissions_object,
            member< smt_token_emissions_object, asset_symbol_type, &smt_token_emissions_object::symbol >,
            const_mem_fun< smt_token_emissions_object, time_point_sec, &smt_token_emissions_object::schedule_end_time >
         >
      >
   >,
   allocator< smt_token_emissions_object >
> smt_token_emissions_index;

} } // namespace clout::chain

FC_REFLECT_ENUM( clout::chain::smt_phase,
                  (setup)
                  (setup_completed)
                  (ico)
                  (ico_completed)
                  (launch_failed)
                  (launch_success)
)

FC_REFLECT( clout::chain::smt_token_object::smt_market_maker_state,
   (clout_balance)
   (token_balance)
   (reserve_ratio)
)

FC_REFLECT( clout::chain::smt_token_object,
   (id)
   (liquid_symbol)
   (control_account)
   (desired_ticker)
   (phase)
   (current_supply)
   (total_vesting_fund_smt)
   (total_vesting_shares)
   (total_vesting_fund_ballast)
   (total_vesting_shares_ballast)
   (pending_rewarded_vesting_shares)
   (pending_rewarded_vesting_smt)
   (reward_balance)
   (recent_claims)
   (last_reward_update)
   (last_virtual_emission_time)
   (allow_downvotes)
   (market_maker)
   (allow_voting)
   (cashout_window_seconds)
   (reverse_auction_window_seconds)
   (vote_regeneration_period_seconds)
   (votes_per_regeneration_period)
   (content_constant)
   (percent_curation_rewards)
   (author_reward_curve)
   (curation_reward_curve)
   (max_supply)
)

FC_REFLECT( clout::chain::smt_ico_object,
   (id)
   (symbol)
   (contribution_begin_time)
   (contribution_end_time)
   (launch_time)
   (clout_satoshi_min)
   (min_unit_ratio)
   (max_unit_ratio)
   (contributed)
   (processed_contributions)
)

FC_REFLECT( clout::chain::shared_smt_generation_unit,
   (clout_unit)
   (token_unit) )

FC_REFLECT( clout::chain::smt_ico_tier_object,
   (id)
   (symbol)
   (clout_satoshi_cap)
   (generation_unit)
)

FC_REFLECT( clout::chain::shared_smt_emissions_unit,
   (token_unit)
)

FC_REFLECT( clout::chain::smt_token_emissions_object,
   (id)
   (symbol)
   (schedule_time)
   (emissions_unit)
   (interval_seconds)
   (emission_count)
   (lep_time)
   (rep_time)
   (lep_abs_amount)
   (rep_abs_amount)
   (lep_rel_amount_numerator)
   (rep_rel_amount_numerator)
   (rel_amount_denom_bits)
   (floor_emissions)
)

FC_REFLECT( clout::chain::smt_contribution_object,
   (id)
   (symbol)
   (contributor)
   (contribution_id)
   (contribution)
)

CHAINBASE_SET_INDEX_TYPE( clout::chain::smt_token_object, clout::chain::smt_token_index )
CHAINBASE_SET_INDEX_TYPE( clout::chain::smt_ico_object, clout::chain::smt_ico_index )
CHAINBASE_SET_INDEX_TYPE( clout::chain::smt_token_emissions_object, clout::chain::smt_token_emissions_index )
CHAINBASE_SET_INDEX_TYPE( clout::chain::smt_contribution_object, clout::chain::smt_contribution_index )
CHAINBASE_SET_INDEX_TYPE( clout::chain::smt_ico_tier_object, clout::chain::smt_ico_tier_index )
