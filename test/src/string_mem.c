
#include "bmlib.h"
#include "testing.h"

void test_string_mem()
{
    char buffer1[10], buffer2[10];
    char *tmp;
    int i;

    test_group_start("string_mem");

    /* memset */
    for(i = 0; i < 10; i++)
        buffer1[i] = 0x33;

    memset((void *)buffer1, 0x44, 9);

    for(i = 0; i < 9; i++)
        test_eq("memset test A1", 0x44, buffer1[i]);
    test_eq("memset test A2", 0x33, buffer1[9]);


    memset((void *)buffer1, -1, 8);

    for(i = 0; i < 8; i++)
        test_eq("memset test B1", -1, buffer1[i]);
    test_eq("memset test B2", 0x44, buffer1[8]);
    test_eq("memset test B3", 0x33, buffer1[9]);


    /* memcpy */
    memset(buffer2, 0x11, 10);
    strcpy(buffer1, "ABC");
    memcpy(buffer2, buffer1, 4); /* buffer2 = A B C \'0 0x11 0x11 ... */

    test_eq("memset A1", 0, strcmp(buffer2, "ABC"));
    for(i = 4; i < 10; i++)
        test_eq("memset A2", 0x11, buffer2[i]);


    test_group_end();
}
