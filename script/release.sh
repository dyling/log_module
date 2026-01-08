#/bin/bash

current_date=$(date '+%Y%m%d')

# docker build -t robot:$current_date -f ./DockerfileUsr .
docker build -t ubuntu20.04:$current_date .
