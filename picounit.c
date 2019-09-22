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

#include <string.h>  /* strcmp */
#include <stdio.h>   /* prinf */

#define TERM_COLOR_CODE 0x1B
#define TERM_COLOR_RED "[1;31m"
#define TERM_COLOR_GREEN "[1;32m"
#define TERM_COLOR_RESET "[0m"

static unsigned g_num_asserts = 0;
static unsigned g_num_passed  = 0;
static unsigned g_num_failed  = 0;
static unsigned g_num_suites = 0;

int
pico_assert (int b_passed,
             const char* const p_expr,
             const char* const p_file,
             int line)
{
    g_num_asserts++;

    if (b_passed)
    {
        return 1;
    }
    else
    {
        printf("(%c%sFAILED%c%s: %s (%d): %s)\n",
                TERM_COLOR_CODE, TERM_COLOR_RED,
                TERM_COLOR_CODE, TERM_COLOR_RESET,
                p_file, line, p_expr);

        return 0;
    }
}

int
pico_assert_str_eq (const char* const p_left_str,
                    const char* const p_right_str,
                    const char* const p_file,
                    int line)
{
    g_num_asserts++;

    if ((NULL != p_left_str) && (NULL != p_right_str) &&
        (0 == strcmp(p_left_str, p_right_str)))
    {
        return 1;
    }
    else
    {
        printf("(%c%sFAILED%c%s: %s (%d): \"%s\" == \"%s\")\n",
                TERM_COLOR_CODE, TERM_COLOR_RED,
                TERM_COLOR_CODE, TERM_COLOR_RESET,
                p_file, line, p_left_str, p_right_str);

        return 0;
    }
}

void
pico_run_test (const char* const p_name,
               pico_test_t p_test,
               pico_setup_t p_setup,
               pico_teardown_t p_teardown)
{
    if (NULL != p_setup)
    {
        p_setup();
    }

    printf("Running: %s ", p_name);

    if (!p_test())
    {
        g_num_failed++;
    }
    else
    {
        printf("(%c%sOK%c%s)\n", TERM_COLOR_CODE, TERM_COLOR_GREEN,
                                 TERM_COLOR_CODE, TERM_COLOR_RESET);

        g_num_passed++;
    }

    if (NULL != p_teardown)
    {
        p_teardown();
    }
}

void
pico_run_suite (const char* const p_name, pico_suite_t p_suite)
{
    printf("===============================================================\n");
    printf("Running: %s\n", p_name);
    printf("---------------------------------------------------------------\n");
    p_suite();
    g_num_suites++;
}

void
pico_print_stats()
{
    printf("===============================================================\n");
    printf("Summary: Passed: %u, Failed: %u, Total: %u, Suites: %u, Asserts: %u\n",
            g_num_passed,  g_num_failed, g_num_passed + g_num_failed, 
            g_num_suites, g_num_asserts);
}

/* EoF */
