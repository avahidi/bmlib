baremetallib
============

Library of stuff often needed in bare metal projects.


Who should use this?
--------------------

This is probably only useful to people working on embedded systems.


Usage
-----
Normally, you should just add the src folder to your project but define your
own bmconfig.h file. 

While not recommended you could also just use the static library built in
the project. You can easily corss-compile and supply your own flags. Here 
are two examples for ARMv7 and ARMv8 respectively:


    make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-a7"


    make CROSS_COMPILE=aarch64-linux-gnu- UFLAGS="-mcpu=cortex-a53 -march=armv8-a -mgeneral-regs-only"

