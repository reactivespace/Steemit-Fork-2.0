#pragma once

#include <vector>

namespace clout{ namespace plugins { namespace p2p {

#ifdef IS_TEST_NET
const std::vector< std::string > default_seeds;
#else
const std::vector< std::string > default_seeds = {
   "seed-east.cloutit.com:2001",          // cloutit
   "seed-central.cloutit.com:2001",       // cloutit
   "seed-west.cloutit.com:2001",          // cloutit
   "52.74.152.79:2001",                   // smooth.witness
   "anyx.io:2001",                        // anyx
   "seed.liondani.com:2016",              // liondani
   "gtg.clout.house:2001",                // gtg
   "seed.jesta.us:2001",                  // jesta
   "lafonaclout.com:2001",                // lafona
   "clout-seed.altcap.io:40696",          // ihashfury
   "seed.roelandp.nl:2001",               // roelandp
   "seed.timcliff.com:2001",              // timcliff
   "cloutseed.clayop.com:2001",           // clayop
   "seed.cloutviz.com:2001",              // ausbitbank
   "clout-seed.lukestokes.info:2001",     // lukestokes
   "seed.cloutian.info:2001",             // drakos
   "seed.followbtcnews.com:2001",         // followbtcnews
   "node.mahdiyari.info:2001",            // mahdiyari
   "seed.riverclout.com:2001",            // riverhead
   "seed1.blockbrothers.io:2001",         // blockbrothers
   "cloutseed-fin.privex.io:2001",        // privex
   "seed.yabapmatt.com:2001"              // yabapmatt
};
#endif

} } } // clout::plugins::p2p
