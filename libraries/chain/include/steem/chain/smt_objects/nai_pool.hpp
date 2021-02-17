#pragma once
#include <clout/chain/database.hpp>
#include <clout/protocol/asset_symbol.hpp>

namespace clout { namespace chain {

   void replenish_nai_pool( database& db );
   void remove_from_nai_pool( database &db, const asset_symbol_type& a );

} } // clout::chain
