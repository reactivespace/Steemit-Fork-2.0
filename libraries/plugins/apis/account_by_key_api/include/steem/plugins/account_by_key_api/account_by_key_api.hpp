#pragma once
#include <clout/plugins/json_rpc/utility.hpp>

#include <clout/protocol/types.hpp>

#include <fc/optional.hpp>
#include <fc/variant.hpp>
#include <fc/vector.hpp>

namespace clout { namespace plugins { namespace account_by_key {

namespace detail
{
   class account_by_key_api_impl;
}

struct get_key_references_args
{
   std::vector< clout::protocol::public_key_type > keys;
};

struct get_key_references_return
{
   std::vector< std::vector< clout::protocol::account_name_type > > accounts;
};

class account_by_key_api
{
   public:
      account_by_key_api();
      ~account_by_key_api();

      DECLARE_API( (get_key_references) )

   private:
      std::unique_ptr< detail::account_by_key_api_impl > my;
};

} } } // clout::plugins::account_by_key

FC_REFLECT( clout::plugins::account_by_key::get_key_references_args,
   (keys) )

FC_REFLECT( clout::plugins::account_by_key::get_key_references_return,
   (accounts) )
