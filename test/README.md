# test

This directory is intended for PlatformIO Unit Testing and project tests.

Unit Testing is a software testing method by which individual units of
source code, sets of one or more MCU program modules together with associated
control data, usage procedures, and operating procedures, are tested to
determine whether they are fit for use. Unit testing finds problems early
in the development cycle.

* [More information about PlatformIO Unit Testing](https://docs.platformio.org/page/plus/unit-testing.html)

## Esp32 build

### OpenBSD

* [platformio-openbsd-tool-esptool](https://github.com/lotherk/platformio-openbsd-tool-esptool)
* [ESP-IDF Visual Studio Code Extension](https://github.com/espressif/vscode-esp-idf-extension)

### Linux

The tool-chain which are the tools necessary to compile the programs:

```sh
cd ~
mkdir esp32
cd esp32
sudo apt-get install git wget make libncurses-dev flex bison gperf python python-serial
# // >> Here we download and install an x86-64 build chain (compilers)
wget https://dl.espressif.com/dl/xtensa-esp32-elf-linux64-1.22.0-61-gab8375a-5.2.0.tar.gz
tar -xvf xtensa-esp32-elf-linux64-1.22.0-61-gab8375a-5.2.0.tar.gz
sudo mv xtensa-esp32-elf /opt
export PATH=/opt/xtensa-esp32-elf/bin:$PATH
# // << End of build chain install
```

With the tools in place, what remains is the creation of the development environment
using the ESP-IDF framework:

```sh
git clone --recursive https://github.com/espressif/esp-idf.git
cd esp-idf
git submodule update --init
export IDF_PATH=~/esp32/esp-idf
```

At this point, we should have all the ingredients necessary for building an application.
The recommended way to build an application is to clone the Espressif template app
and use that as the basis for your own work.

```sh
cd ~/esp32
mkdir apps
cd apps
git clone https://github.com/espressif/esp-idf-template.git myapp
cd myapp
make menuconfig
```

We are now ready to compile our application

## Micropython

[Micropython](https://micropython.org/download/ESP32_GENERIC/)

## PlatformIO

```sh
pio run -v -t upload
```
