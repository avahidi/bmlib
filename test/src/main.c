
#include "bmlib.h"
#include "testing.h"


extern void test_div();
extern void test_string();
extern void test_string_strtok();
extern void test_string_mem();
extern void test_stdio();


int main(int argc, char **argv)
{
    test_start();

    test_div();
    test_string();
    test_string_strtok();
    test_string_mem();
    test_stdio();

    test_end();

}
