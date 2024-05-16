add_test([=[CheckColisions.Test1]=]  C:/Users/Jean/parking/build/tests.exe [==[--gtest_filter=CheckColisions.Test1]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[CheckColisions.Test1]=]  PROPERTIES WORKING_DIRECTORY C:/Users/Jean/parking/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  tests_TESTS CheckColisions.Test1)
