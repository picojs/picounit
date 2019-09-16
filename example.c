/*=============================================================================
 * MIT License
 *
 * Copyright (c) 2019 James McLean
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
=============================================================================*/

#include "picounit.h"

#include <stdio.h>

static unsigned g_fix = 0;

bool test_passing1()
{
    PICO_ASSERT(true);
    PICO_ASSERT_EQ(42, 42);
    PICO_ASSERT_EQ_STR("towel", "towel");
    return true;
}

void test_setup()
{
    g_fix = 42;
}

void test_teardown()
{
    g_fix = 0;
}

bool test_passing2()
{
    PICO_ASSERT(42 == g_fix);
    PICO_ASSERT_EQ_STR("frog", "frog");
    return true;
}

bool test_failing()
{
    PICO_ASSERT(true);
    PICO_ASSERT(false); // Fails here
    PICO_ASSERT(true);
    return true;
}

bool suite_passing()
{
    PICO_RUN_TEST(test_passing1);
    PICO_RUN_TEST_ST(test_passing2, test_setup, test_teardown);
    return true;
}

bool suite_failing()
{
    PICO_RUN_TEST(test_passing1);
    PICO_RUN_TEST(test_failing);
    PICO_RUN_TEST(test_passing1);
    return true;
}


int main (int argc, char** argv)
{
    PICO_RUN_SUITE(suite_passing);
    PICO_RUN_SUITE(suite_failing);
    return 0;
}
