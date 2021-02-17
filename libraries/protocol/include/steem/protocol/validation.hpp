
#pragma once

#include <clout/protocol/base.hpp>
#include <clout/protocol/block_header.hpp>
#include <clout/protocol/asset.hpp>

#include <fc/utf8.hpp>

namespace clout { namespace protocol {

inline bool is_asset_type( asset asset, asset_symbol_type symbol )
{
   return asset.symbol == symbol;
}

inline void validate_account_name( const string& name )
{
   FC_ASSERT( is_valid_account_name( name ), "Account name ${n} is invalid", ("n", name) );
}

inline void validate_permlink( const string& permlink )
{
   FC_ASSERT( permlink.size() < CLOUT_MAX_PERMLINK_LENGTH, "permlink is too long" );
   FC_ASSERT( fc::is_utf8( permlink ), "permlink not formatted in UTF8" );
}

inline void validate_smt_symbol( const asset_symbol_type& symbol )
{
   symbol.validate();
   FC_ASSERT( symbol.space() == asset_symbol_type::smt_nai_space, "legacy symbol used instead of NAI" );
   FC_ASSERT( symbol.is_vesting() == false, "liquid variant of NAI expected");
}

/**
 * Determine if a price complies with Tick Pricing Rules.
 *
 * - For prices involving Clout Dollars (CBD), the base asset must be CBD.
 * - For prices involving SMT assets, the base asset must be CLOUT.
 * - The quote must be a power of 10.
 *
 * \param  price The price to check for Tick Pricing compliance
 * \return true  If price conforms to Tick Pricing Rules
 */
inline bool is_tick_pricing( const price& p )
{
   if ( p.base.symbol == CBD_SYMBOL )
   {
      if ( p.quote.symbol != CLOUT_SYMBOL )
         return false;
   }
   else if ( p.base.symbol == CLOUT_SYMBOL )
   {
      if ( p.quote.symbol.space() != asset_symbol_type::smt_nai_space )
         return false;

      if ( p.quote.symbol.is_vesting() )
         return false;
   }
   else
   {
      return false;
   }

   share_type tmp = p.quote.amount;
   while ( tmp > 9 && tmp % 10 == 0 )
      tmp /= 10;

   if ( tmp != 1 )
      return false;

   return true;
}

/**
 * Validate a price complies with Tick Pricing Rules.
 *
 * - For prices involving Clout Dollars (CBD), the base asset must be CBD.
 * - For prices involving SMT assets, the base asset must be CLOUT.
 * - The quote must be a power of 10.
 *
 * \param price The price to perform Tick Pricing Rules validation
 * \throw fc::assert_exception If the price does not conform to Tick Pricing Rules
 */
inline void validate_tick_pricing( const price& p )
{
   if ( p.base.symbol == CBD_SYMBOL )
   {
      FC_ASSERT( p.quote.symbol == CLOUT_SYMBOL, "Only CLOUT can be paired with CBD as the base symbol." );
   }
   else if ( p.base.symbol == CLOUT_SYMBOL )
   {
      FC_ASSERT( p.quote.symbol.space() == asset_symbol_type::smt_nai_space, "Only tokens can be paired with CLOUT as the base symbol." );
      FC_ASSERT( p.quote.symbol.is_vesting() == false, "Quote symbol cannot be a vesting symbol." );
   }
   else
   {
      FC_ASSERT( false, "CLOUT and CBD are the only valid base symbols." );
   }

   share_type tmp = p.quote.amount;
   while ( tmp > 9 && tmp % 10 == 0 )
      tmp /= 10;
   FC_ASSERT( tmp == 1, "The quote amount must be a power of 10." );
}

} }
