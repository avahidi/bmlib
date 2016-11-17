/*
 * minimal testing framework
 */
#include <stdbool.h>

#include "bmlib.h"
#include "testing.h"


/* instead of the whole <stdlib.h>: */
extern void exit(int);

static bool inside_group = false;
static int total_cnt = 0;
static int total_fail = 0;
static int group_cnt = 0;
static int group_fail = 0;
static int groups = 0;

void fatal(const char *msg)
{
    printf( "FATAL ERROR: %s\n", msg);
    exit(20);
}


void assert(const char *msg, bool b)
{
    if(!b)
        fatal(msg);
}

/*
 * groups
 */
void test_group_start(const char *name)
{
    printf("  GROUP '%s'...\n", name);

    assert("group not correctly ended", !inside_group);

    inside_group = true;
    groups++;
    group_fail = 0;
    group_cnt = 0;
}

void test_group_end()
{
    assert("Test group end without start", inside_group);
    inside_group = false;
    total_cnt += group_cnt;
    total_fail += group_fail;

    if(group_fail)
        printf("  group failed with %d errors in %d tests\n", group_fail, group_cnt);
}

/*
 * all tests
 */
void test_start()
{
    printf("TESTING started\n");
}

void test_end()
{
    printf("TESTING ended\n");

    if(total_fail) {
        printf("FAILURE: %d tests of %d FAILED\n", total_fail, total_cnt);
        exit(20);
    } else {
        printf("SUCCESS: %d tests in %d groups PASSED\n", total_cnt, groups);
    }
}

/*
 * backend
 */

void test_record0_(char *msg, bool v,
                   const char *op, int lineno, const char *file)
{
    group_cnt++;
    if(!v) {
        group_fail++;
        printf("    FAILED: %s in %s:%d\n      ", msg, file, lineno);
        printf(op);
        printf("\n");
    }
}

void test_record1_(char *msg, bool v, const char *op,
                   int a,
                   int lineno, const char *file)
{
    group_cnt++;
    if(!v) {
        group_fail++;
        printf("    FAILED: %s in %s:%d\n      ", msg, file, lineno);
        printf(op, a);
        printf("\n");
    }
}

void test_record2_(char *msg, bool v, const char *op,
                   int a, int b,
                   int lineno, const char *file)
{
    group_cnt++;
    if(!v) {
        group_fail++;
        printf("    FAILED: %s in %s:%d\n      ", msg, file, lineno);
        printf(op, a, b);
        printf("\n");
    }
}

void test_record3_(char *msg, bool v, const char *op,
                   int a, int b, int c,
                   int lineno, const char *file)
{
    group_cnt++;
    if(!v) {
        group_fail++;
        printf("    FAILED: %s in %s:%d\n      ", msg, file, lineno);
        printf(op, a, b, c);
        printf("\n");
    }
}
