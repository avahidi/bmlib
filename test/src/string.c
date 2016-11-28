
#include "bmlib.h"
#include "testing.h"


void test_string()
{
    char buffer[10];
    char *tmp;

    test_group_start("string");
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
