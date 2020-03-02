#ifndef __BMCONFIG_H__
#define __BMCONFIG_H__

/*
 * This is the library configuration file, which defines what parts are included.
 * Comment definitions to disable specific parts.
 *
 * Note that you can provide a different bmconfig.h file by setting the CONFIG make variable.
 */

#define BMLIB_HAS_PRINTF_X64 /* %X prints 64-bit hex */
#define BMLIB_HAS_PRINTF /* printf, sprintf */
#define BMLIB_HAS_STRING /* strlen, strcpy etc */
#define BMLIB_HAS_STRING_MEM /* memset + memcpy */
#define BMLIB_HAS_STRING_STRTOK /* strtok, strtok_r */
#define BMLIB_HAS_DIV10  /* divide by 10 to avoid */


#endif /* __BMCONFIG_H__ */
