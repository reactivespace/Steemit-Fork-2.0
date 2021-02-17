#!/bin/bash

echo /tmp/core | tee /proc/sys/kernel/core_pattern
ulimit -c unlimited

# if we're not using PaaS mode then start cloutd traditionally with sv to control it
if [[ ! "$USE_PAAS" ]]; then
  mkdir -p /etc/service/cloutd
  cp /usr/local/bin/clout-sv-run.sh /etc/service/cloutd/run
  chmod +x /etc/service/cloutd/run
  runsv /etc/service/cloutd
elif [[ "$IS_TESTNET" ]]; then
  /usr/local/bin/pulltestnetscripts.sh
else
  /usr/local/bin/startpaascloutd.sh
fi
