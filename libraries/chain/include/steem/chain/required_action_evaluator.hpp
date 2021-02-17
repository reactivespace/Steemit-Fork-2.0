#pragma once

#include <clout/protocol/clout_required_actions.hpp>

#include <clout/chain/evaluator.hpp>

namespace clout { namespace chain {

using namespace clout::protocol;

#ifdef IS_TEST_NET
CLOUT_DEFINE_ACTION_EVALUATOR( example_required, required_automated_action )
#endif

CLOUT_DEFINE_ACTION_EVALUATOR( smt_ico_launch, required_automated_action )
CLOUT_DEFINE_ACTION_EVALUATOR( smt_ico_evaluation, required_automated_action )
CLOUT_DEFINE_ACTION_EVALUATOR( smt_token_launch, required_automated_action )
CLOUT_DEFINE_ACTION_EVALUATOR( smt_refund, required_automated_action )
CLOUT_DEFINE_ACTION_EVALUATOR( smt_contributor_payout, required_automated_action )
CLOUT_DEFINE_ACTION_EVALUATOR( smt_founder_payout, required_automated_action )

} } //clout::chain
