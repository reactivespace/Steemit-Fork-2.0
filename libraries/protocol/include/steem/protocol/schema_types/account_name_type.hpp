
#pragma once

#include <clout/schema/abstract_schema.hpp>
#include <clout/schema/schema_impl.hpp>

#include <clout/protocol/types.hpp>

namespace clout { namespace schema { namespace detail {

//////////////////////////////////////////////
// account_name_type                        //
//////////////////////////////////////////////

struct schema_account_name_type_impl
   : public abstract_schema
{
   CLOUT_SCHEMA_CLASS_BODY( schema_account_name_type_impl )
};

}

template<>
struct schema_reflect< clout::protocol::account_name_type >
{
   typedef detail::schema_account_name_type_impl           schema_impl_type;
};

} }

namespace fc {

template<>
struct get_typename< clout::protocol::account_name_type >
{
   static const char* name()
   {
      return "clout::protocol::account_name_type";
   }
};

}
