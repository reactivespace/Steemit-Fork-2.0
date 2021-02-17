#pragma once

#include <clout/protocol/types.hpp>
#include <clout/protocol/transaction.hpp>
#include <clout/protocol/block_header.hpp>

#include <clout/plugins/json_rpc/utility.hpp>
#include <clout/plugins/transaction_status/transaction_status_objects.hpp>

namespace clout { namespace plugins { namespace transaction_status_api {

struct find_transaction_args
{
   chain::transaction_id_type transaction_id;
   fc::optional< fc::time_point_sec > expiration;
};

struct find_transaction_return
{
   transaction_status::transaction_status status;
   fc::optional< uint32_t > block_num;
};

} } } // clout::transaction_status_api

FC_REFLECT( clout::plugins::transaction_status_api::find_transaction_args, (transaction_id)(expiration) )
FC_REFLECT( clout::plugins::transaction_status_api::find_transaction_return, (status)(block_num) )
