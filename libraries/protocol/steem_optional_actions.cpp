#include <clout/protocol/validation.hpp>
#include <clout/protocol/clout_optional_actions.hpp>
#include <clout/protocol/smt_util.hpp>

namespace clout { namespace protocol {

#ifdef IS_TEST_NET
void example_optional_action::validate()const
{
   validate_account_name( account );
}
#endif

void smt_token_emission_action::validate() const
{
   validate_account_name( control_account );
   validate_smt_symbol( symbol );
   FC_ASSERT( emissions.empty() == false, "Emissions cannot be empty" );
   for ( const auto& e : emissions )
   {
      FC_ASSERT( smt::unit_target::is_valid_emissions_destination( e.first ),
         "Emissions destination ${n} is invalid", ("n", e.first) );
      FC_ASSERT( e.second > 0, "Emissions must be greater than 0" );
   }
}

} } //clout::protocol
