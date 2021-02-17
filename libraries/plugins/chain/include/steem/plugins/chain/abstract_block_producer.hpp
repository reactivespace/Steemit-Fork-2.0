#pragma once

#include <fc/time.hpp>

#include <clout/chain/database.hpp>

namespace clout { namespace plugins { namespace chain {
   
class abstract_block_producer {
public:
   virtual ~abstract_block_producer() = default;

   virtual clout::chain::signed_block generate_block(
      fc::time_point_sec when,
      const clout::chain::account_name_type& witness_owner,
      const fc::ecc::private_key& block_signing_private_key,
      uint32_t skip = clout::chain::database::skip_nothing) = 0;
};

} } } // clout::plugins::chain
