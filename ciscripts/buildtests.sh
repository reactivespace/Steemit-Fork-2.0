#!/bin/bash
set -e
sudo docker build --build-arg CI_BUILD=1 --build-arg BUILD_STEP=1 -t=cloutit/clout:tests .
sudo docker run -v $WORKSPACE:/var/jenkins cloutit/clout:tests cp -r /var/cobertura /var/jenkins
# make docker cleanup after itself and delete all exited containers
sudo docker rm -v $(docker ps -a -q -f status=exited) || true