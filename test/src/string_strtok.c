
#include "bmlib.h"
#include "testing.h"




static void test_one(const char *str, const char *delim,
		     const char **expected, int _r)
{
    int i;
    char buffer[1024];
    char *save, *token;

    strcpy(buffer, str);

    for(i = 0; expected[i]; i++) {

	if(_r)
 	    token = strtok_r( i == 0 ? buffer : 0, delim, &save);
	else
 	    token = strtok( i == 0 ? buffer : 0, delim);

	test("strtok/strtok_r", !strcmp(expected[i], token));
    }

    /* check it is not returning more */
    if(_r)
	token = strtok_r(0, delim, &save);
    else
	token = strtok(0, delim);

    test("strtok/strtok_r returning more tokens?", !token);
}

void test_string_strtok()
{
    const char *delim = " ,\t";

    const char *text1 = " abc 1234 , 5\t6";
    const char *answer1[] = { "abc", "1234", "5", "6", 0 };

    const char *text2 = "  a   ";
    const char *answer2[] = { "a", 0 };

    const char *text3 = "b";
    const char *answer3[] = { "b", 0 };

    const char *empty[] = { 0 };
    char *null = 0;

    test_group_start("string_strtok");

    test_one(text1, delim, answer1, 0);
    test_one(text1, delim, answer1, 1);

    test_one(text2, delim, answer2, 0);
    test_one(text2, delim, answer2, 1);

    test_one(text3, delim, answer3, 0);
    test_one(text3, delim, answer3, 1);


    /* some edge cases */
    test_one("", delim, empty, 0);
    test_one("", delim, empty, 1);


    test("NULL str & save -> NULL",  !strtok_r(0, delim, &null));

    test_group_end();
}
