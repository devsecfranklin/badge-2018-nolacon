#!/usr/bin/env bash
#
# SPDX-FileCopyrightText: 2023 DE:AD:10:C5 <franklin@dead10c5.org>
#
# SPDX-License-Identifier: GPL-3.0-or-later

set -eu

#Black        0;30     Dark Gray     1;30
#Red          0;31     Light Red     1;31
#Green        0;32     Light Green   1;32
#Brown/Orange 0;33     Yellow        1;33
#Blue         0;34     Light Blue    1;34
#Purple       0;35     Light Purple  1;35
#Cyan         0;36     Light Cyan    1;36
#Light Gray   0;37     White         1;37

RED='\033[0;31m'
LRED='\033[1;31m'
LGREEN='\033[1;32m'
LBLUE='\033[1;34m'
CYAN='\033[0;36m'
LPURP='\033[1;35m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

MY_OS="unknown"
CONTAINER=false
DOCUMENTATION=false

# Check if we are inside a docker container
function check_docker() {
  if [ -f /.dockerenv ]; then
    echo -e "${CYAN}Containerized build environment...${NC}"
    CONTAINER=true
  else
    echo -e "${CYAN}NOT a containerized build environment...${NC}"
  fi
}

function detect_os() {
  # check for the /etc/os-release file
  OS_RELEASE=$(cat /etc/os-release | grep "^ID=" | cut -d"=" -f2)
  if [ -n "${OS_RELEASE}" ]; then
    echo -e "${CYAN}Found /etc/os-release file: ${OS_RELEASE}${NC}"
  fi

  # Check uname (Linux, OpenBSD, Darwin)
  MY_UNAME=$(uname)
  if [ -n "${OS_RELEASE}" ]; then
    echo -e "${CYAN}Found uname: ${MY_UNAME}${NC}"
  fi

  if [ "${MY_UNAME}" == "OpenBSD" ]; then
    echo -e "${CYAN}Detected OpenBSD${NC}"
    MY_OS="openbsd"
  elif [ "${MY_UNAME}" == "Darwin" ]; then
    echo -e "${CYAN}Detected MacOS${NC}"
    MY_OS="mac"
  elif [ -f "/etc/redhat-release" ]; then
    echo -e "${CYAN}Detected Red Hat/CentoOS/RHEL${NC}"
    MY_OS="rh"
  elif [ "$(grep -Ei 'debian|buntu|mint' /etc/*release)" ]; then
    echo -e "${CYAN}Detected Debian/Ubuntu/Mint${NC}"
    MY_OS="deb"
  elif grep -q Microsoft /proc/version; then
    echo -e "${CYAN}Detected Windows pretending to be Linux${NC}"
    MY_OS="win"
  else
    echo -e "${YELLOW}Unrecongnized architecture.${NC}"
    exit 1
  fi
}

function main() {
  check_docker
  detect_os
  if [ "${MY_OS}" == "openbsd" ]; then
    #cd /usr/ports/devel/arduino && make && doas make install
    doas pkg_add arduino-esp8266 py3-pip arduino-esp32 pycharm
    #cd /usr/ports/devel/pycharm && doas make && doas make install
    pip install platformio
    pio init
  else
    echo -e "${YELLOW}This script runs on OpenBSD.${NC}"
    exit 1
  fi
}

main "$@"
