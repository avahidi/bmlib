
#include "bmlib.h"
#include "testing.h"


void test_div()
{
   test_group_start("div");

   test_eq("div A", 5, divu10(55));

   test_group_end();
}

void test_strxxx()
{
    char buffer[10];
    char *tmp;

    test_group_start("strxxx");
    /* strlen */
    test_eq("strlen test A", 4, strlen("ABCD"));
    test_eq("strlen test B", 0, strlen(""));

    /* strchr */
    tmp = "ABC";
    test_eq("strchr test A",  tmp + 2, strchr(tmp, 'C'));
    test_eq("strchr test B", 0, strchr(tmp, 'D'));

    tmp = "ABCC";
    test_eq("strchr test B", tmp + 2, strchr(tmp, 'C'));

    tmp = "\0BCD";
    test_eq("strchr test D", 0, strchr(tmp, 'D'));

    /* strcmp */
    test_eq("strcmp test A", 0, strcmp("ABCD", "ABCD"));
    test_eq("strcmp test B", 0, strcmp("", ""));

    test_neq("strcmp test C", 0, strcmp("ABC", "ABZ"));
    test_eq("strcmp test D", 'A', strcmp("A", ""));
    test_eq("strcmp test E", -'A', strcmp("", "A"));

    /* strncmp */
    test_eq("strncmp test A", 0, strncmp("ABCD", "ABCD", 4));
    test_eq("strncmp test A", 0, strncmp("ABCx", "ABCy", 3));
    test_eq("strncmp test A", 0, strncmp("foo", "bar", 0));

    /* strcpy */
    strcpy(buffer, "ABCD");
    test_eq("strcpy test A", 0, strcmp(buffer, "ABCD"));

    strcpy(buffer, "");
    test_eq("strcpy test B", 0, strcmp(buffer, ""));


    /* strncpy */
    strcpy(buffer, "xxx?"); /* 4 = ?, 5 = '\0' */
    strncpy(buffer, "ABCD", 3);
    test_eq("strn test A", 0, strcmp(buffer, "ABC?"));

    strncpy(buffer, "", 1);
    test_eq("strncpy test B", 0, strlen(buffer));

    buffer[4] = buffer[5] = buffer[6] = buffer[7] = '!';
    strncpy(buffer, "ABCD", 8);
    test_eq("strncpy test C1", 0, strcmp(buffer, "ABCD"));
    test_eq("strncpy test C2", 0, buffer[4] | buffer[5] | buffer[6] | buffer[7]);
    test_group_end();
}

void test_memxxx()
{
    char buffer1[10], buffer2[10];
    char *tmp;
    int i;

    test_group_start("memxxx");

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

void test_printf()
{
    char buffer[100];

    test_group_start("print");

    /* snprintf */
    snprintf(buffer, 100, "AB%d%c%s%x", 23, 'c', "xyz", 0x123);
    test_eq("snprintf A", 0, strcmp(buffer, "AB23cxyz00000123"));


    snprintf(buffer, 4, "%s", "ABCDEF");
    test_eq("snprintf B", 0, strcmp(buffer, "ABC"));

    snprintf(buffer, 5, "%x", 666);
    test_eq("snprintf C", 0, strcmp(buffer, "0000"));

    test_group_end();
}

int main(int argc, char **argv)
{
    test_start();

    test_div();
    test_strxxx();
    test_memxxx();
    test_printf();

    test_end();

}
