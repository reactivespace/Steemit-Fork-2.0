#pragma once
#include <clout/protocol/block_header.hpp>
#include <clout/protocol/transaction.hpp>

namespace clout { namespace protocol {

   struct signed_block : public signed_block_header
   {
      checksum_type calculate_merkle_root()const;
      vector<signed_transaction> transactions;
   };

} } // clout::protocol

FC_REFLECT_DERIVED( clout::protocol::signed_block, (clout::protocol::signed_block_header), (transactions) )
