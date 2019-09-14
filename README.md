# PicoUnit

## Introduction

PicoUnit is a minimal, yet powerful, unit testing framework written in C99 suitable for general and embedded development.

## API

#### PICO_ASSERT(p_expr)

Assert that the given expression evaluates to `true`. If the expression evalutes to `false`, execution of the current test and containing test suite abort.

- p_expr - The expression to evaluate

#### PICO_ASSERT_MSG(p_msg, p_expr)

Same as the *ASSERT* macro, however it accepts a message describing the test.

- p_msg  The message to display
- p_expr The expression to evaluate

#### PICO_RUN_TEST(p_test)

Runs a unit test function.

- p_test The test function to execute

#### PICO_RUN_TEST_ST(p_test, p_setup, p_teardown)

Runs a unit test function with setup and teardown functions.

- p_test The test function to execute
- p_setup Setup function that is run before the test function
- p_teardown Teardown function that is run after the test function

#### PICO_RUN_SUITE(p_suite)

- p_suite The test suite to run


