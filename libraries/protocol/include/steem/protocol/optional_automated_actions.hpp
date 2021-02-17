#pragma once

#include <clout/protocol/clout_optional_actions.hpp>

#include <clout/protocol/operation_util.hpp>

namespace clout { namespace protocol {

   /** NOTE: do not change the order of any actions or it will trigger a hardfork.
    */
   typedef fc::static_variant<
            smt_token_emission_action
#ifdef IS_TEST_NET
            ,example_optional_action
#endif
         > optional_automated_action;

} } // clout::protocol

CLOUT_DECLARE_OPERATION_TYPE( clout::protocol::optional_automated_action );

FC_REFLECT_TYPENAME( clout::protocol::optional_automated_action );
