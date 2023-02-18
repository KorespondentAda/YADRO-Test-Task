cmake_minimum_required(VERSION 3.10)

project(CSVReader VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

#configure_file(TutorialConfig.h.in TutorialConfig.h)

# TODO Windows file naming? Is needed?
#if (UNIX OR APPLE)
#	set(APPNAME "csvreader")
#else()
#	set(APPNAME "csvreader.exe")
#endif()

add_executable(csvreader main.cpp)

#target_include_directories(CSVReader
#PUBLIC ${PROJECT_BINARY_DIR})
