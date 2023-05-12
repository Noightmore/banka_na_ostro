#!/bin/bash

# This script computes the test coverage of the codebase.

function compute_coverage()
{
    for file in $(find . -name '*.cpp')
    do
        gcov "$file"
    done

  #CMakeFiles/AllTests.dir/tests/
   lcov --capture --directory . --capture --no-checksum --output-file coverage.info
   lcov --remove coverage.info '/usr/*' '*/tests/*' '*/pages/*' --output-file coverage.info
   lcov --remove coverage.info  --output-file coverage.info
   lcov --list coverage.info --output-file coverage.txt
}

compute_coverage