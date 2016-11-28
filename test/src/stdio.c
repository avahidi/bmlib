
#include "bmlib.h"
#include "testing.h"

void test_stdio()
{
    char buffer[100];

    test_group_start("stdio");

    /* snprintf */
    snprintf(buffer, 100, "AB%d%c%s%x", 23, 'c', "xyz", 0x123);
    test_eq("snprintf A", 0, strcmp(buffer, "AB23cxyz00000123"));


    snprintf(buffer, 4, "%s", "ABCDEF");
    test_eq("snprintf B", 0, strcmp(buffer, "ABC"));

    snprintf(buffer, 5, "%x", 666);
    test_eq("snprintf C", 0, strcmp(buffer, "0000"));

    test_group_end();
}
