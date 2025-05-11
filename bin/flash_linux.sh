#!/usr/bin/env bash
#
# SPDX-FileCopyrightText: ©2018-2025 franklin <franklin@bitsmasher.net>
#
# SPDX-License-Identifier: MIT

# ChangeLog:
#
# v0.1 | 03/22/2018 15:26 | initial version | franklin

set -o nounset # Treat unset variables as an error
#IFS=$'\n\t'

if [ ! -d "docs" ] && [ ! -d "bin" ]; then
  echo "Run script from top level of repo"
  exit 1
fi

function setup_tools() {
  sudo apt-get update && sudo apt-get install arduino xvfb
  /sbin/start-stop-daemon --start --quiet --pidfile /tmp/custom_xvfb_1.pid \
    --make-pidfile --background --exec /usr/bin/Xvfb -- :1 -ac \
    -screen 0 1280x1024x16
  sleep 3
  export DISPLAY=:1.0
}

function setup_boards() {
  arduino --pref "boardsmanager.additional.urls=http://arduino.esp8266.com/stable/package_esp8266com_index.json" --save-prefs
  arduino --install-boards esp8266:esp8266 --save-prefs
}

function setup_libraries() {
  arduino --install-library "APA102"
}

function main() {
  setup_tools
  setup_boards
  setup_libraries

  arduino --verify --board esp8266:esp8266:generic $PWD/nola_con/nola_con.ino
} # //main()

if [ -z "$ARGS" ]; then
  main "$@"
else
  main "${ARGS}"
fi
