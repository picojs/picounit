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

/*
 * PicoUnit implementation
 */

#include "picounit.h"

#include <stddef.h>
#include <stdio.h>

#define TERM_COLOR_CODE 0x1B
#define TERM_COLOR_RED "[1;31m"
#define TERM_COLOR_GREEN "[1;32m"
#define TERM_COLOR_RESET "[0m"

static unsigned g_tests_passed = 0;

bool
pico_assert (bool b_passed,
             const char* const p_expr,
             const char* const p_file,
             int line)
{
    if (b_passed)
    {
        return true;
    } else
    {
        printf("Test failed: %s (%d): %s\n", p_file, line, p_expr);
        return false;
    }
}

bool
pico_run_test (const char* const p_name,
               pico_test_t p_test,
               pico_setup_t p_setup,
               pico_teardown_t p_teardown)
{
    if (NULL != p_setup)
    {
        p_setup();
    }

    printf("Running test: %s\n", p_name);

    if (!p_test())
        return false;

    if (NULL != p_teardown)
    {
        p_teardown();
    }

    g_tests_passed++;

    return true;
}

bool
pico_run_suite (const char* const p_name, pico_suite_t p_suite)
{
    printf("==================================================\n");
    printf("Running suite: %s\n", p_name);
    printf("==================================================\n");

    if (!p_suite())
    {
        printf("%c%sFailed!%c%s\n",
               TERM_COLOR_CODE, TERM_COLOR_RED,
               TERM_COLOR_CODE, TERM_COLOR_RESET);

        return false;
    }
    else
    {
        printf("%c%sSuccess!%c%s",
               TERM_COLOR_CODE, TERM_COLOR_GREEN,
               TERM_COLOR_CODE, TERM_COLOR_RESET);

        printf("(%u tests passed)\n", g_tests_passed);

        return true;
    }
}

/* EoF */
