#pragma once

#include <clout/protocol/block.hpp>

namespace clout { namespace chain {

struct transaction_notification
{
   transaction_notification( const clout::protocol::signed_transaction& tx ) : transaction(tx)
   {
      transaction_id = tx.id();
   }

   clout::protocol::transaction_id_type          transaction_id;
   const clout::protocol::signed_transaction&    transaction;
};

} }
