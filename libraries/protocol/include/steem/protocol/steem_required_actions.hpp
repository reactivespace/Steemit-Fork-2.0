#pragma once
#include <clout/protocol/types.hpp>
#include <clout/protocol/base.hpp>
#include <clout/protocol/asset.hpp>
#include <clout/protocol/misc_utilities.hpp>

namespace clout { namespace protocol {

#ifdef IS_TEST_NET
   struct example_required_action : public base_operation
   {
      account_name_type account;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const{ a.insert(account); }

      friend bool operator==( const example_required_action& lhs, const example_required_action& rhs );
   };
#endif

   struct smt_refund_action : public base_operation
   {
      account_name_type contributor;
      asset_symbol_type symbol;
      uint32_t          contribution_id;
      asset             refund;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( contributor ); }

      friend bool operator==( const smt_refund_action& lhs, const smt_refund_action& rhs );
   };

   struct contribution_payout
   {
      asset payout;
      bool  to_vesting;

      friend bool operator==( const contribution_payout& rhs, const contribution_payout& lhs );
   };

   struct smt_contributor_payout_action : public base_operation
   {
      account_name_type    contributor;
      asset_symbol_type    symbol;
      uint32_t             contribution_id;
      asset                contribution;
      std::vector< contribution_payout > payouts;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( contributor ); }

      friend bool operator==( const smt_contributor_payout_action& lhs, const smt_contributor_payout_action& rhs );
   };

   struct smt_founder_payout_action : public base_operation
   {
      asset_symbol_type                                   symbol;
      std::map< account_name_type, std::vector< contribution_payout > > account_payouts;
      share_type                                          market_maker_clout  = 0;
      share_type                                          market_maker_tokens = 0;
      share_type                                          reward_balance      = 0;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const
      {
         for ( auto& entry : account_payouts )
            a.insert( entry.first );
      }

      friend bool operator==( const smt_founder_payout_action& lhs, const smt_founder_payout_action& rhs );
   };

   struct smt_ico_launch_action : public base_operation
   {
      account_name_type control_account;
      asset_symbol_type symbol;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( control_account ); }

      friend bool operator==( const smt_ico_launch_action& lhs, const smt_ico_launch_action& rhs );
   };

   struct smt_ico_evaluation_action : public base_operation
   {
      account_name_type control_account;
      asset_symbol_type symbol;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( control_account ); }

      friend bool operator==( const smt_ico_evaluation_action& lhs, const smt_ico_evaluation_action& rhs );
   };

   struct smt_token_launch_action : public base_operation
   {
      account_name_type control_account;
      asset_symbol_type symbol;

      void validate()const;
      void get_required_active_authorities( flat_set<account_name_type>& a )const { a.insert( control_account ); }

      friend bool operator==( const smt_token_launch_action& lhs, const smt_token_launch_action& rhs );
   };
} } // clout::protocol

#ifdef IS_TEST_NET
FC_REFLECT( clout::protocol::example_required_action, (account) )
#endif

FC_REFLECT( clout::protocol::smt_refund_action, (contributor)(symbol)(contribution_id)(refund) )
FC_REFLECT( clout::protocol::contribution_payout, (payout)(to_vesting) )
FC_REFLECT( clout::protocol::smt_contributor_payout_action, (contributor)(symbol)(contribution_id)(contribution)(payouts) )
FC_REFLECT( clout::protocol::smt_founder_payout_action, (symbol)(account_payouts)(market_maker_clout)(market_maker_tokens)(reward_balance) )
FC_REFLECT( clout::protocol::smt_ico_launch_action, (control_account)(symbol) )
FC_REFLECT( clout::protocol::smt_ico_evaluation_action, (control_account)(symbol) )
FC_REFLECT( clout::protocol::smt_token_launch_action, (control_account)(symbol) )
