#pragma once

#include <clout/chain/evaluator.hpp>

#include <clout/private_message/private_message_operations.hpp>
#include <clout/private_message/private_message_plugin.hpp>

namespace clout { namespace private_message {

CLOUT_DEFINE_PLUGIN_EVALUATOR( private_message_plugin, clout::private_message::private_message_plugin_operation, private_message )

} }
