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
Normally, you should just add the *src* folder to your project then define your
own *bmconfig.h* file.

While not recommended you could also just use the static library built by
the Makefile.
It is straight-forward to cross-compile or supply your own compilation flags.
To cross-compile for Raspberry Pi 2:

    make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-a7"

For 64-bit ARM:

    make CROSS_COMPILE=aarch64-linux-gnu- UFLAGS="-mcpu=cortex-a53 -march=armv8-a -mgeneral-regs-only"

and so on...
