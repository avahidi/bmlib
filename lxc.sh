#!/bin/bash

#
# compile everything for different architectures in an LXC container
#

set -ex

lxc delete -f bmlib || echo "No previous container found"
lxc launch images:ubuntu/18.04 bmlib
lxc exec bmlib -- useradd -m -s /bin/bash -G sudo -p "" user

lxc file push -r  . bmlib/home/user/bmlib

sleep 5

lxc exec bmlib -- su -l user << EOF
set -ex
sudo apt update
sudo apt install --no-install-recommends -y git mg make build-essential gcc-arm-none-eabi gcc-aarch64-linux-gnu gcc-mips-linux-gnu gcc-powerpc-linux-gnu gcc-riscv64-linux-gnu

sudo chown user:user -R ~/bmlib
cd bmlib

# amd64
make 
make test
make stats
mv build ~/bmlib_amd64

# arm32m
make UFLAGS="-m32" stats 
mv build ~/bmlib_x86

# arm32m
make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-m4" stats 
mv build ~/bmlib_arm32m

# arm32
make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-a7" stats 
mv build ~/bmlib_arm32

# arm64
make CROSS_COMPILE=aarch64-linux-gnu- UFLAGS="-mcpu=cortex-a53 -march=armv8-a -mgeneral-regs-only" stats
mv build ~/bmlib_arm64

# MIPS32
make CROSS_COMPILE=mips-linux-gnu- stats
mv build ~/bmlib_mips32

# PPC32
make CROSS_COMPILE=powerpc-linux-gnu- UFLAGS="-mcpu=power8" stats 
mv build ~/bmlib_ppc32

# PPC64
make CROSS_COMPILE=powerpc-linux-gnu- UFLAGS="-mcpu=powerpc64" stats 
mv build ~/bmlib_ppc64

# RISCV-64
make CROSS_COMPILE=riscv64-linux-gnu- stats 
mv build ~/bmlib_riscv64
EOF

# log into container
lxc exec bmlib -- su -l user

