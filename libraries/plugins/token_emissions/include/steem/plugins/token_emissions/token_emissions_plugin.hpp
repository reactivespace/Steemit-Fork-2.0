#pragma once
#include <clout/chain/clout_fwd.hpp>
#include <clout/plugins/chain/chain_plugin.hpp>

#include <appbase/application.hpp>

namespace clout { namespace plugins { namespace token_emissions {

#define CLOUT_TOKEN_EMISSIONS_PLUGIN_NAME "token_emissions"

namespace detail { class token_emissions_impl; }

class token_emissions_plugin : public appbase::plugin< token_emissions_plugin >
{
   public:
      token_emissions_plugin();
      virtual ~token_emissions_plugin();

      APPBASE_PLUGIN_REQUIRES( (clout::plugins::chain::chain_plugin) )

      static const std::string& name() { static std::string name = CLOUT_TOKEN_EMISSIONS_PLUGIN_NAME; return name; }

      virtual void set_program_options( boost::program_options::options_description& cli, boost::program_options::options_description& cfg ) override;
      virtual void plugin_initialize( const boost::program_options::variables_map& options ) override;
      virtual void plugin_startup() override;
      virtual void plugin_shutdown() override;

   private:
      std::unique_ptr< detail::token_emissions_impl > my;
};

} } } // clout::plugins::token_emissions

