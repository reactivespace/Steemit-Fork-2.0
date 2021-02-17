#include <clout/protocol/sps_operations.hpp>

#include <clout/protocol/validation.hpp>

namespace clout { namespace protocol {

void create_proposal_operation::validate()const
{
   validate_account_name( creator );
   validate_account_name( receiver );

   FC_ASSERT( end_date > start_date, "end date must be greater than start date" );

   FC_ASSERT( daily_pay.amount >= 0, "Daily pay can't be negative value" );
   FC_ASSERT( daily_pay.symbol.asset_num == CLOUT_ASSET_NUM_CBD, "Daily pay should be expressed in CBD");

   FC_ASSERT( !subject.empty(), "subject is required" );
   FC_ASSERT( subject.size() <= CLOUT_PROPOSAL_SUBJECT_MAX_LENGTH, "Subject is too long");
   FC_ASSERT( fc::is_utf8( subject ), "Subject is not valid UTF8" );

   FC_ASSERT( !permlink.empty(), "permlink is required" );
   validate_permlink(permlink);
}

void update_proposal_votes_operation::validate()const
{
   validate_account_name( voter );
   FC_ASSERT(proposal_ids.empty() == false);
   FC_ASSERT(proposal_ids.size() <= CLOUT_PROPOSAL_MAX_IDS_NUMBER);
}

void remove_proposal_operation::validate() const
{
   validate_account_name(proposal_owner);
   FC_ASSERT(proposal_ids.empty() == false);
   FC_ASSERT(proposal_ids.size() <= CLOUT_PROPOSAL_MAX_IDS_NUMBER);
}

} } //clout::protocol
