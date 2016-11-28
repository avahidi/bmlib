
#include "bmlib.h"
#include "testing.h"


void test_div()
{
   test_group_start("div");

   test_eq("div A", 5, divu10(55));

   test_group_end();
}
