#pragma once

#include <clout/protocol/asset.hpp>

namespace clout { namespace chain { namespace util {

using clout::protocol::asset;
using clout::protocol::price;

inline asset to_cbd( const price& p, const asset& clout )
{
   FC_ASSERT( clout.symbol == CLOUT_SYMBOL );
   if( p.is_null() )
      return asset( 0, CBD_SYMBOL );
   return clout * p;
}

inline asset to_clout( const price& p, const asset& cbd )
{
   FC_ASSERT( cbd.symbol == CBD_SYMBOL );
   if( p.is_null() )
      return asset( 0, CLOUT_SYMBOL );
   return cbd * p;
}

} } }
