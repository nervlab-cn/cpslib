cmake_minimum_required(VERSION 2.8.12)

project(cps)
set(CMAKE_CXX_FLAGS_DEBUG "-g3 -Wall -g -ggdb -fPIC -Wno-unused-function")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -Wno-unused-function")
#set(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage -static-libgcc")
#set(CMAKE_LINK_LIBRARY_FLAG "-lgcov --coverage")

set(CMAKE_SKIP_RPATH FALSE)
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_SKIP_INSTALL_RPATH FALSE)

set(CMAKE_CXX_STANDARD 11)
set(LIB_VERSION 1.0.0)

include_directories(.)
include_directories(utils)

aux_source_directory(utils SRC_LIST)
aux_source_directory(cpp SRC_LIST)

if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    aux_source_directory(osx SRC_LIST)
else(CMAKE_SYSTEM_NAME MATCHES "Linux")
    aux_source_directory(linux SRC_LIST)
endif()

add_library(${PROJECT_NAME} SHARED ${SRC_LIST} linux/proc_keys.h)

SET(LIBRARY_OUTPUT_PATH lib)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${LIB_VERSION})
if (CMAKE_SYSTEM_NAME MATCHES "Darwin")
    target_link_libraries(${PROJECT_NAME} "-framework CoreFoundation -framework IOKit")
else(CMAKE_SYSTEM_NAME MATCHES "Linux")

endif()

add_executable(cps-test-c cps-test.c)
target_link_libraries(cps-test-c ${PROJECT_NAME})

add_executable(cps-test-cpp cppps-test.cpp)
target_link_libraries(cps-test-cpp ${PROJECT_NAME})

add_executable(strtok-c strtok_test.c)
target_link_libraries(strtok-c ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION lib)

