#!/bin/sh 

find . | grep -v ".git" | grep -v ".idea" | grep -v "cmake-build-debug" | grep -v ".clang-format" | grep -e "\.c" -e "\.cpp" -e "\.inl" -e "\.h" | xargs -n 1 clang-format -i

