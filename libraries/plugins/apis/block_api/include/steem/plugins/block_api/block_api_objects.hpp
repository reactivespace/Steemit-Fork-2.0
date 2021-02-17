#pragma once
#include <clout/chain/account_object.hpp>
#include <clout/chain/block_summary_object.hpp>
#include <clout/chain/comment_object.hpp>
#include <clout/chain/global_property_object.hpp>
#include <clout/chain/history_object.hpp>
#include <clout/chain/clout_objects.hpp>
#include <clout/chain/transaction_object.hpp>
#include <clout/chain/witness_objects.hpp>
#include <clout/chain/database.hpp>

namespace clout { namespace plugins { namespace block_api {

using namespace clout::chain;

struct api_signed_block_object : public signed_block
{
   api_signed_block_object( const signed_block& block ) : signed_block( block )
   {
      block_id = id();
      signing_key = signee();
      transaction_ids.reserve( transactions.size() );
      for( const signed_transaction& tx : transactions )
         transaction_ids.push_back( tx.id() );
   }
   api_signed_block_object() {}

   block_id_type                 block_id;
   public_key_type               signing_key;
   vector< transaction_id_type > transaction_ids;
};

} } } // clout::plugins::database_api

FC_REFLECT_DERIVED( clout::plugins::block_api::api_signed_block_object, (clout::protocol::signed_block),
                     (block_id)
                     (signing_key)
                     (transaction_ids)
                  )
