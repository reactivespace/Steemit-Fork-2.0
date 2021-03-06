#pragma once
#include <clout/chain/clout_object_types.hpp>
#include <clout/protocol/transaction.hpp>

namespace clout { namespace plugins { namespace transaction_status {

using namespace clout::chain;

#ifndef CLOUT_TRANSACTION_STATUS_SPACE_ID
#define CLOUT_TRANSACTION_STATUS_SPACE_ID 18
#endif

enum transaction_status_object_type
{
   transaction_status_object_type = ( CLOUT_TRANSACTION_STATUS_SPACE_ID << 8 )
};

enum transaction_status
{
   unknown,                           // Expiration time in future, transaction not included in block or mempool
   within_mempool,                    // Transaction in mempool
   within_reversible_block,           // Transaction has been included in block, block not irreversible
   within_irreversible_block,         // Transaction has been included in block, block is irreversible
   expired_reversible,                // Transaction has expired, transaction is not irreversible (transaction could be in a fork)
   expired_irreversible,              // Transaction has expired, transaction is irreversible (transaction cannot be in a fork)
   too_old                            // Transaction is too old, I don't know about it
};

class transaction_status_object : public object< transaction_status_object_type, transaction_status_object >
{
public:
   template< typename Constructor, typename Allocator >
   transaction_status_object( Constructor&& c, allocator< Allocator > a )
   {
      c( *this );
   }

   transaction_status_object() {}

   id_type                     id;
   transaction_id_type         transaction_id;
   uint32_t                    block_num = 0;
};

typedef oid< transaction_status_object > transaction_status_object_id_type;

struct by_trx_id;
struct by_block_num;
struct by_expiration;

typedef multi_index_container<
   transaction_status_object,
   indexed_by<
      ordered_unique< tag< by_id >, member< transaction_status_object, transaction_status_object_id_type, &transaction_status_object::id > >,
      ordered_unique< tag< by_trx_id >, member< transaction_status_object, transaction_id_type, &transaction_status_object::transaction_id > >,
      ordered_unique< tag< by_block_num >,
         composite_key< transaction_status_object,
            member< transaction_status_object, uint32_t, &transaction_status_object::block_num >,
            member< transaction_status_object, transaction_id_type, &transaction_status_object::transaction_id >
         >,
         composite_key_compare< std::less< uint32_t >, std::less< transaction_id_type > >
      >
   >,
   allocator< transaction_status_object >
> transaction_status_index;



} } } // clout::plugins::transaction_status

FC_REFLECT_ENUM( clout::plugins::transaction_status::transaction_status,
                (unknown)
                (within_mempool)
                (within_reversible_block)
                (within_irreversible_block)
                (expired_reversible)
                (expired_irreversible)
                (too_old) )

FC_REFLECT( clout::plugins::transaction_status::transaction_status_object, (id)(transaction_id)(block_num) )
CHAINBASE_SET_INDEX_TYPE( clout::plugins::transaction_status::transaction_status_object, clout::plugins::transaction_status::transaction_status_index )
