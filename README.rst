bmlib - a bare metal library
============================

Library of stuff often needed in bare metal projects.

It is more or less a small fraction (say 1%) of libc functionality in a tiny tiny package.

Who should use this?
--------------------

This is probably only useful to people working on 32 or 64-bit embedded systems.

Assume you are writing low-level code and want to print some debug messages. bmlib allows you to do that with minimal code additions.


What does it provide?
---------------------

It currently includes the following functions::

    /* from stdio.h */
    void printf(const char *fmt, ...);
    void vprintf(const char *fmt, va_list ap);
    void snprintf(char *buffer, int size, const char *fmt, ...);

    /* from string.h */
    int strlen(const char *s);
    void strcpy(char *dst, const char *src);
    void strncpy(char *dst, const char *src, int n);
    char *strchr(char *s, char c);
    int strcmp(const char *s1, const char *s2);
    int strncmp(const char *s1, const char *s2, int n);
    void memcpy(void *dst, const void *src, int n);
    void memset(void *dst, int c, int n);
    char *strtok(char *str, const char *delim);
    char *strtok_r(char *str, const char *delim, char **save);

    /* from elsewhere */
    uint32_t divu10(uint32_t n); /* to avoid libgcc dependency of __eabi_div */


Note that if you use printf() you need to provide your own *int putchar(int c)*

Building
--------

To cross-compile you need to set some make variables::

    # Raspberry Pi 2 (32-bit ARMv7):
    make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-a7"

    # Raspberry Pi 3 (64-bit ARMv8):
    make CROSS_COMPILE=aarch64-linux-gnu- UFLAGS="-mcpu=cortex-a53 -march=armv8-a -mgeneral-regs-only"

    # ... and so on.

The user-supplied UFLAGS is appended to the current compiler flags CFLAGS.


Footprint
---------

The code has been written to have minimal dynamic footprint (i.e. stack usage), although the exact numbers depend on your application.

To check static footprint (i.e. code size) for a particular configuration, use "make stats"::

    make stats
    ...   
   text	   data	    bss	    dec	    hex	filename
    545	      0	      8	    553	    229	string.o (ex build/libbm.a)
   1336	      0	      0	   1336	    538	stdio.o (ex build/libbm.a)
     99	      0	      0	     99	     63	div10.o (ex build/libbm.a)
   1980	      0	      8	   1988	    7c4	(TOTALS)


The corresponding numbers for the full configuration on all architectures are::


   text	   data	    bss	    dec	    hex	target
   1980	      0	      8	   1988	    7c4	AMD64
   1953	      0	      4	   1957	    7a5	x86
    837	      0	      4	    841	    349	ARM32m (ARMv7-M)
   1315	      0	      4	   1319	    527	ARM32  (ARMv7-A)
   1735	      0	      8	   1743	    6cf	ARM64  (ARMv8-A)
   1832	      0	     16	   1848	    738	MIPS32
   1899	      0	      4	   1903	    76f	POWER8
   1907	      0	      4	   1911	    777	PPC64
   1047	      0	      8	   1055	    41f	RISC-V

These numbers can be reduced significantly by disabling things you don't need. For example, strtok() and strtok_r() are rarely used and 64-bit pointer support in printf() does not make sense in a 32-bit system.

Have a look at the configuration file ( src/config/bmconfig.h ) for more information.


License
-------

This library is made available under the zlib license, see LICENSE.

