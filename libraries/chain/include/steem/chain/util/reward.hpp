#pragma once

#include <clout/chain/util/asset.hpp>

#include <clout/protocol/asset.hpp>
#include <clout/protocol/config.hpp>
#include <clout/protocol/types.hpp>
#include <clout/protocol/misc_utilities.hpp>

#include <fc/reflect/reflect.hpp>

#include <fc/uint128.hpp>

namespace clout { namespace chain { namespace util {

using clout::protocol::asset;
using clout::protocol::price;
using clout::protocol::share_type;

using fc::uint128_t;

struct comment_reward_context
{
   share_type           rshares;
   uint16_t             reward_weight = 0;
   uint128_t            total_claims;
   share_type           reward_fund;
   protocol::curve_id   reward_curve = protocol::quadratic;
   uint128_t            content_constant = CLOUT_CONTENT_CONSTANT_HF0;
};

uint64_t get_rshare_reward( const comment_reward_context& ctx );

inline uint128_t get_content_constant_s()
{
   return CLOUT_CONTENT_CONSTANT_HF0; // looking good for posters
}

uint128_t evaluate_reward_curve( const uint128_t& rshares, const protocol::curve_id& curve = protocol::quadratic, const uint128_t& var1 = CLOUT_CONTENT_CONSTANT_HF0 );

} } } // clout::chain::util

FC_REFLECT( clout::chain::util::comment_reward_context,
   (rshares)
   (reward_weight)
   (total_claims)
   (reward_fund)
   (reward_curve)
   (content_constant)
   )
