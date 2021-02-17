#include <clout/plugins/follow/follow_operations.hpp>

#include <clout/protocol/operation_util_impl.hpp>

namespace clout { namespace plugins{ namespace follow {

void follow_operation::validate()const
{
   FC_ASSERT( follower != following, "You cannot follow yourself" );
}

void reblog_operation::validate()const
{
   FC_ASSERT( account != author, "You cannot reblog your own content" );
}

} } } //clout::plugins::follow

CLOUT_DEFINE_OPERATION_TYPE( clout::plugins::follow::follow_plugin_operation )
