#!/usr/bin/env bash
#
# SPDX-FileCopyrightText: ©2018-2025 franklin <franklin@bitsmasher.net>
#
# SPDX-License-Identifier: MIT

# ChangeLog:
#
# v0.1 05/09/2018 12:15

set -o nounset # Treat unset variables as an error
#IFS=$'\n\t'

# Starts the Arduino IDE using the docker image.
# see also: ...

#    -v /dev/ttyACM0:/dev/ttyACM0 \
#    -v /dev/ttyUSB0:/dev/ttyUSB0 \
docker run \
  -it \
  --rm \
  --network=host \
  --privileged \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  -v /dev:/dev \
  -v $HOME/topics:/topics \
  -v $HOME/topics/arduino:/home/developer/Arduino \
  --name arduino \
  nola_con_2018_badge \
  arduino
