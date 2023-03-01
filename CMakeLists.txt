cmake_minimum_required(VERSION 3.10)

project(CSVReader VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(csvreader main.cpp Csv.cpp Log.cpp)

enable_testing()
set(test_dir ${CMAKE_SOURCE_DIR}/tests)

function(do_test arg result)
  add_test(NAME Comp_${arg} COMMAND csvreader ${test_dir}/${arg})
  set_tests_properties(Comp_${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

add_test(NAME Runs COMMAND csvreader ${test_dir}/file.csv)
add_test(NAME NotRuns COMMAND csvreader ${test_dir}/fail.csv)
add_test(NAME Empty COMMAND csvreader)
add_test(NAME EmptyFields COMMAND csvreader ${test_dir}/emptyFields.csv)
set_tests_properties(NotRuns EmptyFields PROPERTIES WILL_FAIL True)
set_tests_properties(Empty PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*")
do_test(file "Error: can't open file.*")
do_test(empty.csv "Error: Empty CSV")
do_test(short.csv "Error: Invalid number of fields in record")
do_test(long.csv "Error: Invalid number of fields in record")
do_test(noNum.csv "Error: Row number is not a valid number")

# Process over number of tests
foreach(num RANGE 7)
	add_test(NAME Result_${num} COMMAND
		${CMAKE_SOURCE_DIR}/test.sh ${CMAKE_BINARY_DIR}/csvreader ${test_dir}/in${num}.csv ${test_dir}/out${num}.csv)
endforeach()
