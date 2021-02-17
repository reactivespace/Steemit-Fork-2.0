#pragma once

#include <fc/container/flat.hpp>
#include <clout/protocol/operations.hpp>
#include <clout/protocol/transaction.hpp>

#include <fc/string.hpp>

namespace clout { namespace app {

using namespace fc;

void operation_get_impacted_accounts(
   const clout::protocol::operation& op,
   fc::flat_set<protocol::account_name_type>& result );

void transaction_get_impacted_accounts(
   const clout::protocol::transaction& tx,
   fc::flat_set<protocol::account_name_type>& result
   );

} } // clout::app
