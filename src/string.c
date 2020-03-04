
#include <bmlib.h>

#ifdef BMLIB_HAS_STRING

/*
 * string functions.
 * some are optimised for size not efficiency or libc conforming!
 */

int strlen(const char *s)
{
    int ret = 0;
    while(*s++ != '\0')
        ret++;
    return ret;
}

void strcpy(char *dst, const char *src)
{
    for(; *src != '\0'; )
        *dst++ = *src++;
    *dst = '\0';
}

void strncpy(char *dst, const char *src, int n)
{
    char *tmp = dst;
    for(; n > 0 && *src != '\0'; n--)
        *dst++ = *src++;

    while(n-- > 0)
        *dst++ = '\0';
}


char *strchr(const char *s, char c)
{
    do {
        if(*s == c)
            return (char *)s;
    } while(*s++ != '\0');

    return 0;
}

int strcmp(const char *s1, const char *s2)
{
    while(*s1 == *s2 && *s1 != '\0') {
        s1++;
        s2++;
    }
    return (int)(*s1) - (int)(*s2);

}

int strncmp(const char *s1, const char *s2, int n)
{
    int diff;
    while(n--) {
        diff = (int)(*s1) - (int)(*s2);
        if(diff || *s1 == '\0')
            return diff;
        s1++;
        s2++;
    }
    return 0;
}
#endif /*  BMLIB_HAS_STRING */

#ifdef BMLIB_HAS_STRING_MEM
void memcpy(void *dst, const void *src, int n)
{
    char *out = (char *)dst;
    const char *in = (const char *)src;

    while(n-- > 0) {
        *out++ = *in++;
    }
}

void memset(void *dst, int c, int n)
{
    char *out = (char *)dst;

    while(n-- > 0) {
        *out++ = c;
    }
}
#endif /* BMLIB_HAS_STRING_MEM */

#ifdef BMLIB_HAS_STRING_STRTOK
char *strtok(char *str, const char *delim)
{
    static char *save;
    return strtok_r(str, delim, &save);
}

char *strtok_r(char *str, const char *delim, char **save)
{
    char *e;

    if(!str) {
	str = *save;
	if(!str)
	    return str;
    }

    /* delim before */
    for(;  *str != '\0' && strchr(delim, *str); str++)
	;

    if( *str == '\0')
	return 0;

    /* end of text */
    for(e = str; *e != '\0' && !strchr(delim, *e); e++)
	;

    if( *e != '\0')
	*e++ = '\0';

    *save = e;
    return str;
}

#endif /* BMLIB_HAS_STRING_STRTOK */
