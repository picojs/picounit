/*==============================================================================
 * Copyright (C) 2019 James McLean
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA
 * ===========================================================================*/

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
