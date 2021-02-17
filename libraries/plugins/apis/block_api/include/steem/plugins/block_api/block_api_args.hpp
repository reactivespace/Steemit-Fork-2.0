#pragma once
#include <clout/plugins/block_api/block_api_objects.hpp>

#include <clout/protocol/types.hpp>
#include <clout/protocol/transaction.hpp>
#include <clout/protocol/block_header.hpp>

#include <clout/plugins/json_rpc/utility.hpp>

namespace clout { namespace plugins { namespace block_api {

/* get_block_header */

struct get_block_header_args
{
   uint32_t block_num;
};

struct get_block_header_return
{
   optional< block_header > header;
};

/* get_block */
struct get_block_args
{
   uint32_t block_num;
};

struct get_block_return
{
   optional< api_signed_block_object > block;
};

} } } // clout::block_api

FC_REFLECT( clout::plugins::block_api::get_block_header_args,
   (block_num) )

FC_REFLECT( clout::plugins::block_api::get_block_header_return,
   (header) )

FC_REFLECT( clout::plugins::block_api::get_block_args,
   (block_num) )

FC_REFLECT( clout::plugins::block_api::get_block_return,
   (block) )

