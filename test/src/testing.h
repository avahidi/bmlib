/*
 * minimal testing framework
 */

#ifndef __TESTING_H__
#define __TESTING_H__

#include <stdbool.h>

#define test(msg, v)                            \
    test_record0(msg, v, "")

#define test_eq(msg, a, b)                                      \
    test_record2(msg, (a) == (b), "%d == %d", (int) a, (int) b)

#define test_neq(msg, a, b)                                     \
    test_record2(msg, (a) != (b), "%d != %d", (int) a, (int) b)


/* helpers */
#define test_record0(msg, v, op)                    \
    test_record0_(msg, v, op, __LINE__, __FILE__)

#define test_record1(msg, v, a, op)                 \
    test_record1_(msg, v, op, a, __LINE__, __FILE__)

#define test_record2(msg, v, op, a, b)                  \
    test_record2_(msg, v, op, a, b, __LINE__, __FILE__)

#define test_record3(msg, v, op, a, b, c)                   \
    test_record3_(msg, v, op, a, b, c, __LINE__, __FILE__)

/* backend functions */
extern void test_record0_(char *msg, bool v, const char *op,
                          int lineno, const char *file);

extern void test_record1_(char *msg, bool v, const char *op,
                          int a,
                          int lineno, const char *file);

extern void test_record2_(char *msg, bool v, const char *op,
                          int a, int b,
                          int lineno, const char *file);

extern void test_record3_(char *msg, bool v, const char *op,
                          int a, int b, int c,
                          int lineno, const char *file);

/* admin functions */

void test_start();
void test_end();

void test_group_start(const char *name);
void test_group_end();

/* the rest */
void fatal(const char *msg);

#endif /* __TESTING_H__ */
