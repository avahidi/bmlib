#ifndef __BMLIB_H__
#define __BMLIB_H__

#include "bmconfig.h"



#ifdef __ASSEMBLER__

#else /* __ASSEMBLER__ */

#include <stdint.h>
#include <stdarg.h>

/* often used attributes */

#define __packed __attribute__((packed))
#define __naked __attribute__((naked))
#define __weak __attribute__((weak))

#ifdef BMLIB_HAS_PRINTF
extern void printf(const char *fmt, ...);
extern void vprintf(const char *fmt, va_list ap);
extern void snprintf(char *buffer, int size, const char *fmt, ...);

extern int putchar(int c); /* defined by YOU */
#endif

#ifdef BMLIB_HAS_STRING
extern int strlen(const char *s);
extern void strcpy(char *dst, const char *src);
extern void strncpy(char *dst, const char *src, int n);

extern char *strchr(char *s, char c);

extern int strcmp(const char *s1, const char *s2);
extern int strncmp(const char *s1, const char *s2, int n);

extern void memcpy(void *dst, const void *src, int n);
extern void memset(void *dst, int c, int n);
#endif

#ifdef BMLIB_HAS_DIV10
extern uint32_t divu10(uint32_t n);
#endif

#endif /* ! __ASSEMBLER__ */

#endif /* __BMLIB_H__ */
