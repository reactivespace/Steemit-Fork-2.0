
#include <clout/chain/clout_object_types.hpp>

#include <clout/chain/index.hpp>

#include <clout/chain/block_summary_object.hpp>
#include <clout/chain/history_object.hpp>
#include <clout/chain/pending_required_action_object.hpp>
#include <clout/chain/pending_optional_action_object.hpp>
#include <clout/chain/smt_objects.hpp>
#include <clout/chain/clout_objects.hpp>
#include <clout/chain/sps_objects.hpp>
#include <clout/chain/transaction_object.hpp>
#include <clout/chain/witness_schedule.hpp>

namespace clout { namespace chain {

void initialize_core_indexes( database& db )
{
   CLOUT_ADD_CORE_INDEX(db, dynamic_global_property_index);
   CLOUT_ADD_CORE_INDEX(db, account_index);
   CLOUT_ADD_CORE_INDEX(db, account_metadata_index);
   CLOUT_ADD_CORE_INDEX(db, account_authority_index);
   CLOUT_ADD_CORE_INDEX(db, witness_index);
   CLOUT_ADD_CORE_INDEX(db, transaction_index);
   CLOUT_ADD_CORE_INDEX(db, block_summary_index);
   CLOUT_ADD_CORE_INDEX(db, witness_schedule_index);
   CLOUT_ADD_CORE_INDEX(db, comment_index);
   CLOUT_ADD_CORE_INDEX(db, comment_content_index);
   CLOUT_ADD_CORE_INDEX(db, comment_vote_index);
   CLOUT_ADD_CORE_INDEX(db, witness_vote_index);
   CLOUT_ADD_CORE_INDEX(db, limit_order_index);
   CLOUT_ADD_CORE_INDEX(db, feed_history_index);
   CLOUT_ADD_CORE_INDEX(db, convert_request_index);
   CLOUT_ADD_CORE_INDEX(db, liquidity_reward_balance_index);
   CLOUT_ADD_CORE_INDEX(db, operation_index);
   CLOUT_ADD_CORE_INDEX(db, account_history_index);
   CLOUT_ADD_CORE_INDEX(db, hardfork_property_index);
   CLOUT_ADD_CORE_INDEX(db, withdraw_vesting_route_index);
   CLOUT_ADD_CORE_INDEX(db, owner_authority_history_index);
   CLOUT_ADD_CORE_INDEX(db, account_recovery_request_index);
   CLOUT_ADD_CORE_INDEX(db, change_recovery_account_request_index);
   CLOUT_ADD_CORE_INDEX(db, escrow_index);
   CLOUT_ADD_CORE_INDEX(db, savings_withdraw_index);
   CLOUT_ADD_CORE_INDEX(db, decline_voting_rights_request_index);
   CLOUT_ADD_CORE_INDEX(db, reward_fund_index);
   CLOUT_ADD_CORE_INDEX(db, vesting_delegation_index);
   CLOUT_ADD_CORE_INDEX(db, vesting_delegation_expiration_index);
   CLOUT_ADD_CORE_INDEX(db, pending_required_action_index);
   CLOUT_ADD_CORE_INDEX(db, pending_optional_action_index);
   CLOUT_ADD_CORE_INDEX(db, smt_token_index);
   CLOUT_ADD_CORE_INDEX(db, account_regular_balance_index);
   CLOUT_ADD_CORE_INDEX(db, account_rewards_balance_index);
   CLOUT_ADD_CORE_INDEX(db, nai_pool_index);
   CLOUT_ADD_CORE_INDEX(db, smt_token_emissions_index);
   CLOUT_ADD_CORE_INDEX(db, smt_contribution_index);
   CLOUT_ADD_CORE_INDEX(db, smt_ico_index);
   CLOUT_ADD_CORE_INDEX(db, smt_ico_tier_index);
   CLOUT_ADD_CORE_INDEX(db, comment_smt_beneficiaries_index);
   CLOUT_ADD_CORE_INDEX(db, proposal_index);
   CLOUT_ADD_CORE_INDEX(db, proposal_vote_index);
}

index_info::index_info() {}
index_info::~index_info() {}

abstract_object::abstract_object() {}
abstract_object::~abstract_object() {}

} }
