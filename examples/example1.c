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

/**
 * For a more complete demonstration, see ex2.c
 */

#include <picounit.h>

/*
 * Passing test. Note that the test function declaration returns an integer
 * value and that the test definition returns 1. All test functions
 * must return a non-zero value.
 */
int
test1 ()
{
    PICOU_ASSERT(2 + 2 == 4);                /* Boolean assertion (ok)         */
    PICOU_ASSERT_STR_EQ("apples", "apples"); /* String equality assertion (ok) */
    return 1;
}

/* Failing test */
int
test2 ()
{
    PICOU_ASSERT(2 + 2 != 4);                 /* Boolean assertion (fails) */
    PICOU_ASSERT_STR_EQ("apples", "oranges"); /* String equality assertion */
                                             /* (fails but never called)  */
    return 1;
}

/* Mixed results */
int
test3 ()
{
    PICOU_ASSERT(2 + 2 == 4);                 /* Boolean assertion (ok)    */
    PICOU_ASSERT_STR_EQ("apples", "oranges"); /* String equality assertion */
                                             /* (fails)                   */
    return 1;
}

/* Test suite container function (multiple test suits can be specified. */
void
test_suite()
{
    PICOU_RUN_TEST(test1);
    PICOU_RUN_TEST(test2);
    PICOU_RUN_TEST(test3);
}

int
main (int argc, char* argv[])
{
    PICOU_RUN_SUITE(test_suite);
    PICOU_PRINT_STATS(); /* Optional */
    return 0;
}
