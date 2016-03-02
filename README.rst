bmlib - a bare metal library
============================

Library of stuff often needed in bare metal projects.


Who should use this?
--------------------

This is probably only useful to people working on 32 or 64-bit embedded systems.


What does it provide?
---------------------

It currently includes the following functions

 * printf() and snprintf()
 * strXXX() and memXXX() from *string.h*
 * divu10() *(to avoid libgcc dependency of __eabi_div )*


Usage
-----

Build a library using the existing Makefile and define your architecture and configuration via variables.

To cross-compile for Raspberry Pi 2 (32-bit ARMv7):

    make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-a7" CONFIG=...

To cross-compile for Raspberry Pi 3 (64-bit ARMv8):

    make CROSS_COMPILE=aarch64-linux-gnu- UFLAGS="-mcpu=cortex-a53 -march=armv8-a -mgeneral-regs-only" CONFIG=...

Notes
 * UFLAGS is added to gcc CFLAGS.
 * CONFIG should point to the folder holding *bmconfig.h*. The default value is *src/config*
 * If you use printf() you need to provide your own *int putchar(int c)*
