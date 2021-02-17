#pragma once

#include <clout/protocol/types.hpp>

#include <fc/reflect/reflect.hpp>

namespace clout { namespace protocol {
struct signed_transaction;
} } // clout::protocol

namespace clout { namespace plugins { namespace rc {

using clout::protocol::account_name_type;
using clout::protocol::signed_transaction;

account_name_type get_resource_user( const signed_transaction& tx );

} } } // clout::plugins::rc
