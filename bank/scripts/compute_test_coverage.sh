#!/bin/bash

# This script computes the test coverage of the codebase.

function compute_coverage()
{
#    for file in $(find . -name '*.cpp')
#    do
#        gcov "$file"
#        echo "$file"
#    done

   pwd
   ls -al
  #CMakeFiles/AllTests.dir/tests/
  # '*/tests/*' '*/pages/*'
   lcov --capture --directory . --capture  --output-file coverage.info
   lcov --remove coverage.info '/usr/*'  --output-file coverage.info
   lcov --remove coverage.info  --output-file coverage.info
   lcov --list coverage.info --output-file coverage.txt
}

compute_coverage