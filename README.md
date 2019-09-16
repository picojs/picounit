PicoUnit
========

PicoUnit is a minimal, yet powerful unit testing framework written in C99. Due to its small footprint, PicoUnit is suitable for embedded as well as general development.

API
--------

#### PICO_ASSERT(expr)

Asserts that the given expression evaluates to `true`. If the expression evalutes to `false`, execution of the current test and containing test suite aborts.

- expr - The expression to evaluate

#### PICO_ASSERT_EQ(left_expr, right_expr)

Asserts that the given expressions evaluates are equal. If the expressions are not equal, execution of the current test and containing test suite aborts.

- left_expr  An expression to compare
- right_expr An expression to compare

#### PICO_ASSERT_STR_EQ(left_str, right_str)

- left_str  A string to compare
- right_str A string to compare

#### PICO_RUN_TEST(p_test)

Runs a unit test function.

- p_test The test function to execute

#### PICO_RUN_TEST_ST(p_test, p_setup, p_teardown)

Runs a unit test function with setup and teardown functions.

- p_test The test function to execute
- p_setup Setup function that is run before the test function
- p_teardown Teardown function that is run after the test function

#### PICO_RUN_SUITE(p_suite)

- p_suite The test suite functionto run

## License
Copyright (c) 2019 James McLean  
Licensed under the MIT license
