#!/bin/bash

# boemiOS still requires an odd compiling
# and installation order to work. This script
# do this

PREFIX=/opt/cross
CC=${PREFIX}/bin/i686-elf-gcc

# 1) install kernel heards to compile libs
make -C ./kernel CC=$CC install-headers

# 2) make libs
make -C ./libc CC=$CC all

# 3) install libc
make -C ./libc install

# 4) make kernel
make -C ./kernel CC=$CC
