#pragma once

#include <clout/protocol/clout_optional_actions.hpp>

#include <clout/chain/evaluator.hpp>

namespace clout { namespace chain {

using namespace clout::protocol;

#ifdef IS_TEST_NET
CLOUT_DEFINE_ACTION_EVALUATOR( example_optional, optional_automated_action )
#endif

CLOUT_DEFINE_ACTION_EVALUATOR( smt_token_emission, optional_automated_action )

} } //clout::chain
