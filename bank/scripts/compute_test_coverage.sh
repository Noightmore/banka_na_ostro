#!/bin/bash

# This script computes the test coverage of the codebase.

function compute_coverage()
{
#    for file in $(find . -name '*.cpp')
#    do
#        gcov "$file"
#        echo "$file"
#    done


   ls -al
   ls -al ./bank
  #CMakeFiles/AllTests.dir/tests/
   sudo lcov --capture --directory ./bank --capture  --output-file coverage.info
   sudo lcov --remove coverage.info '/usr/*' '*/tests/*' '*/pages/*' --output-file coverage.info
   sudo lcov --remove coverage.info  --output-file coverage.info
   sudo lcov --list coverage.info --output-file coverage.txt
}

compute_coverage