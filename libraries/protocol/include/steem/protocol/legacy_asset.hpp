#pragma once

#include <clout/protocol/asset.hpp>

#define CLOUT_SYMBOL_LEGACY_SER_1   (uint64_t(1) | (CLOUT_SYMBOL_U64 << 8))
#define CLOUT_SYMBOL_LEGACY_SER_2   (uint64_t(2) | (CLOUT_SYMBOL_U64 << 8))
#define CLOUT_SYMBOL_LEGACY_SER_3   (uint64_t(5) | (CLOUT_SYMBOL_U64 << 8))
#define CLOUT_SYMBOL_LEGACY_SER_4   (uint64_t(3) | (uint64_t('0') << 8) | (uint64_t('.') << 16) | (uint64_t('0') << 24) | (uint64_t('0') << 32) | (uint64_t('1') << 40))
#define CLOUT_SYMBOL_LEGACY_SER_5   (uint64_t(3) | (uint64_t('6') << 8) | (uint64_t('.') << 16) | (uint64_t('0') << 24) | (uint64_t('0') << 32) | (uint64_t('0') << 40))

namespace clout { namespace protocol {

class legacy_clout_asset_symbol_type
{
   public:
      legacy_clout_asset_symbol_type() {}

      bool is_canon()const
      {   return ( ser == CLOUT_SYMBOL_SER );    }

      uint64_t ser = CLOUT_SYMBOL_SER;
};

struct legacy_clout_asset
{
   public:
      legacy_clout_asset() {}

      template< bool force_canon >
      asset to_asset()const
      {
         if( force_canon )
         {
            FC_ASSERT( symbol.is_canon(), "Must use canonical CLOUT symbol serialization" );
         }
         return asset( amount, CLOUT_SYMBOL );
      }

      static legacy_clout_asset from_amount( share_type amount )
      {
         legacy_clout_asset leg;
         leg.amount = amount;
         return leg;
      }

      static legacy_clout_asset from_asset( const asset& a )
      {
         FC_ASSERT( a.symbol == CLOUT_SYMBOL );
         return from_amount( a.amount );
      }

      share_type                       amount;
      legacy_clout_asset_symbol_type   symbol;
};

} }

namespace fc { namespace raw {

template< typename Stream >
inline void pack( Stream& s, const clout::protocol::legacy_clout_asset_symbol_type& sym )
{
   switch( sym.ser )
   {
      case CLOUT_SYMBOL_LEGACY_SER_1:
      case CLOUT_SYMBOL_LEGACY_SER_2:
      case CLOUT_SYMBOL_LEGACY_SER_3:
      case CLOUT_SYMBOL_LEGACY_SER_4:
      case CLOUT_SYMBOL_LEGACY_SER_5:
         wlog( "pack legacy serialization ${s}", ("s", sym.ser) );
      case CLOUT_SYMBOL_SER:
         pack( s, sym.ser );
         break;
      default:
         FC_ASSERT( false, "Cannot serialize legacy symbol ${s}", ("s", sym.ser) );
   }
}

template< typename Stream >
inline void unpack( Stream& s, clout::protocol::legacy_clout_asset_symbol_type& sym, uint32_t depth )
{
   //  994240:        "account_creation_fee": "0.1 CLOUT"
   // 1021529:        "account_creation_fee": "10.0 CLOUT"
   // 3143833:        "account_creation_fee": "3.00000 CLOUT"
   // 3208405:        "account_creation_fee": "2.00000 CLOUT"
   // 3695672:        "account_creation_fee": "3.00 CLOUT"
   // 4338089:        "account_creation_fee": "0.001 0.001"
   // 4626205:        "account_creation_fee": "6.000 6.000"
   // 4632595:        "account_creation_fee": "6.000 6.000"
   depth++;
   uint64_t ser = 0;

   fc::raw::unpack( s, ser, depth );
   switch( ser )
   {
      case CLOUT_SYMBOL_LEGACY_SER_1:
      case CLOUT_SYMBOL_LEGACY_SER_2:
      case CLOUT_SYMBOL_LEGACY_SER_3:
      case CLOUT_SYMBOL_LEGACY_SER_4:
      case CLOUT_SYMBOL_LEGACY_SER_5:
         wlog( "unpack legacy serialization ${s}", ("s", ser) );
      case CLOUT_SYMBOL_SER:
         sym.ser = ser;
         break;
      default:
         FC_ASSERT( false, "Cannot deserialize legacy symbol ${s}", ("s", ser) );
   }
}

} // fc::raw

inline void to_variant( const clout::protocol::legacy_clout_asset& leg, fc::variant& v )
{
   to_variant( leg.to_asset<false>(), v );
}

inline void from_variant( const fc::variant& v, clout::protocol::legacy_clout_asset& leg )
{
   clout::protocol::asset a;
   from_variant( v, a );
   leg = clout::protocol::legacy_clout_asset::from_asset( a );
}

template<>
struct get_typename< clout::protocol::legacy_clout_asset_symbol_type >
{
   static const char* name()
   {
      return "clout::protocol::legacy_clout_asset_symbol_type";
   }
};

} // fc

FC_REFLECT( clout::protocol::legacy_clout_asset,
   (amount)
   (symbol)
   )
