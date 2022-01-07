bmlib - a bare metal library
============================

Library of things often needed in bare metal projects. It implements 1% of what glibc and musl provide, in a tiny tiny package.


Who should use this?
--------------------

This is probably only useful to people working on 32 or 64-bit embedded systems.

Assume you are writing bare-metal code and want to print some debug messages. bmlib allows you to do that with minimal code.


What does it provide?
---------------------

It currently includes the following functions::

    /* from stdio.h */
    void printf(const char *fmt, ...);
    void vprintf(const char *fmt, va_list ap);
    int snprintf(char *buffer, int size, const char *fmt, ...);

    /* from string.h */
    int strlen(const char *s);
    void strcpy(char *dst, const char *src);
    void strncpy(char *dst, const char *src, int n);
    char *strchr(const char *s, char c);
    int strcmp(const char *s1, const char *s2);
    int strncmp(const char *s1, const char *s2, int n);
    void memcpy(void *dst, const void *src, int n);
    void memset(void *dst, int c, int n);
    char *strtok(char *str, const char *delim);
    char *strtok_r(char *str, const char *delim, char **save);

    /* from elsewhere */
    uint32_t divu10(uint32_t n); /* to avoid libgcc dependency of __eabi_div */


Note that if you use printf() you need to provide your own *int putchar(int c)*.



Is this fully compliant with libc?
----------------------------------

The main goal is to keep things small and simple instead of being 100% libc compliant.

This is what differs:

* printf()/vprintf() don't return the number of printed characters
* formatting flags are not supported in printf() functions
* floating points (%f/e/g/E/G) is not supported
* '%n' is not supported
* '%x' and '%X' print 32 and 64-bit hexadecimals including leading zeros (corresponding to %08x and %016lx)
* '%p' and '%P' start with '0x', behave otherwise like '%x' and '%x'


These were chosen based on authors own experience with bare-metal development, and to keep the library as small as possible. For example not supporting %n was to remove a common `attack vector <https://en.wikipedia.org/wiki/Uncontrolled_format_string>`_, while excluding formatting flags removed something complex but very seldom needed in embedded system (unless to print addresses, which is already supported by %x and %p).


But if you need a fully compliant printf() you might need to use another library such as `Marco Paland's printf implementation <https://github.com/mpaland/printf>`_. Note that this library is 2-3 larger than the entire bmlib, so libc compliance comes with a cost.


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

The code has been written to have minimal dynamic footprint (zero heap usage and minimal stack usage), although the exact numbers depend on your application.

Static footprint (i.e. code size) is easier to quantify with "make stats"::
   
    make stats
    ...    
       text	   data	    bss	    dec	    hex	filename
        626	      0	      8	    634	    27a	string.o (ex build/libbm.a)
       1524	      0	      0	   1524	    5f4	stdio.o (ex build/libbm.a)
        138	      0	      0	    138	     8a	div10.o (ex build/libbm.a)
       2288	      0	      8	   2296	    8f8	(TOTALS)


Note that code size changes drastically with each architecture. Here is ARMv7-M for comparison::

    make CROSS_COMPILE=arm-none-eabi- UFLAGS="-mcpu=cortex-m4" clean stats
    ...
    text	   data	    bss	    dec	    hex	filename
     288	      0	      4	    292	    124	string.o (ex build/libbm.a)
     574	      0	      0	    574	    23e	stdio.o (ex build/libbm.a)
      34	      0	      0	     34	     22	div10.o (ex build/libbm.a)
     896	      0	      4	    900	    384	(TOTALS)


These numbers can be reduced by disabling things you don't need.
Have a look at the configuration file ( src/config/bmconfig.h ) for more information.


License
-------

This library is made available under the zlib license, see LICENSE.

