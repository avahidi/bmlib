
#include "bmlib.h"
#include "testing.h"

void test_stdio()
{
    char buffer[100];
    int n;

    test_group_start("stdio");

    /* snprintf */
    n = snprintf(buffer, 100, "AB%d%c%s%x", 23, 'c', "xyz", 0x123);
    test_eq("snprintf A", 0, strcmp(buffer, "AB23cxyz00000123"));
    test_eq("snprintf A2", n, strlen(buffer) + 1);

    n = snprintf(buffer, 4, "%s", "ABCDEF");
    test_eq("snprintf B", 0, strcmp(buffer, "ABC"));
    test_eq("snprintf B2", n, 4);

    snprintf(buffer, 5, "%x", 666);
    test_eq("snprintf C", 0, strcmp(buffer, "0000"));


    snprintf(buffer, 100, "%x %X %p %P", 0x123, 0x234, 0x345, 0x456);
    test_eq("snprintf D", 0, strcmp(buffer, "00000123 0000000000000234 0x00000345 0x0000000000000456"));

    test_group_end();
}
