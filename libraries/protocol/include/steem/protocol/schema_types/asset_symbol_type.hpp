
#pragma once

#include <clout/schema/abstract_schema.hpp>
#include <clout/schema/schema_impl.hpp>

#include <clout/protocol/asset_symbol.hpp>

namespace clout { namespace schema { namespace detail {

//////////////////////////////////////////////
// asset_symbol_type                        //
//////////////////////////////////////////////

struct schema_asset_symbol_type_impl
   : public abstract_schema
{
   CLOUT_SCHEMA_CLASS_BODY( schema_asset_symbol_type_impl )
};

}

template<>
struct schema_reflect< clout::protocol::asset_symbol_type >
{
   typedef detail::schema_asset_symbol_type_impl           schema_impl_type;
};

} }
