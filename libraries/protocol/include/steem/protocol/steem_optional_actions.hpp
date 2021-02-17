#pragma once
#include <clout/protocol/types.hpp>
#include <clout/protocol/base.hpp>
#include <clout/protocol/asset.hpp>
#include <clout/protocol/smt_operations.hpp>

namespace clout { namespace protocol {

#ifdef IS_TEST_NET
   struct example_optional_action : public base_operation
   {
      account_name_type account;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(account); }
   };
#endif

   struct smt_token_emission_action : public base_operation
   {
      account_name_type                        control_account;
      asset_symbol_type                        symbol;
      time_point_sec                           emission_time;
      flat_map< unit_target_type, share_type > emissions;

      extensions_type                          extensions;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(control_account); }
   };

} } // clout::protocol

#ifdef IS_TEST_NET
FC_REFLECT( clout::protocol::example_optional_action, (account) )
#endif

FC_REFLECT( clout::protocol::smt_token_emission_action, (control_account)(symbol)(emission_time)(emissions)(extensions) )
