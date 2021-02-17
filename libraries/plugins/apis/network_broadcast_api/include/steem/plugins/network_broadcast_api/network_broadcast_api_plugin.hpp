#pragma once
#include <clout/chain/clout_fwd.hpp>
#include <clout/plugins/json_rpc/json_rpc_plugin.hpp>
#include <clout/plugins/chain/chain_plugin.hpp>
#include <clout/plugins/p2p/p2p_plugin.hpp>
#include <clout/plugins/rc/rc_plugin.hpp>

#include <appbase/application.hpp>

#define CLOUT_NETWORK_BROADCAST_API_PLUGIN_NAME "network_broadcast_api"

namespace clout { namespace plugins { namespace network_broadcast_api {

using namespace appbase;

class network_broadcast_api_plugin : public appbase::plugin< network_broadcast_api_plugin >
{
public:
   APPBASE_PLUGIN_REQUIRES(
      (clout::plugins::json_rpc::json_rpc_plugin)
      (clout::plugins::rc::rc_plugin)
      (clout::plugins::chain::chain_plugin)
      (clout::plugins::p2p::p2p_plugin)
   )

   network_broadcast_api_plugin();
   virtual ~network_broadcast_api_plugin();

   static const std::string& name() { static std::string name = CLOUT_NETWORK_BROADCAST_API_PLUGIN_NAME; return name; }

   virtual void set_program_options( options_description& cli, options_description& cfg ) override;
   virtual void plugin_initialize( const variables_map& options ) override;
   virtual void plugin_startup() override;
   virtual void plugin_shutdown() override;

   std::shared_ptr< class network_broadcast_api > api;
};

} } } // clout::plugins::network_broadcast_api
