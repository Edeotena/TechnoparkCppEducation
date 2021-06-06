# CMake generated Testfile for 
# Source directory: /home/timur/prep-2021.01/project/tests
# Build directory: /home/timur/prep-2021.01/project/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(BaseTest "/home/timur/prep-2021.01/project/tests/tests" "/home/timur/prep-2021.01/project/tests/data" "--gtest_filter=-*Extra*")
set_tests_properties(BaseTest PROPERTIES  _BACKTRACE_TRIPLES "/home/timur/prep-2021.01/project/tests/CMakeLists.txt;17;ADD_TEST;/home/timur/prep-2021.01/project/tests/CMakeLists.txt;0;")
add_test(ExtraTest "/home/timur/prep-2021.01/project/tests/tests" "/home/timur/prep-2021.01/project/tests/data" "--gtest_filter=*Extra*")
set_tests_properties(ExtraTest PROPERTIES  _BACKTRACE_TRIPLES "/home/timur/prep-2021.01/project/tests/CMakeLists.txt;21;ADD_TEST;/home/timur/prep-2021.01/project/tests/CMakeLists.txt;0;")
