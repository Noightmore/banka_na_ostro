#!/bin/bash

# This script computes the test coverage of the codebase.

function compute_coverage()
{
   lcov --capture --directory CMakeFiles/AllTests.dir/tests/  --output-file coverage.info
   lcov --remove coverage.info '/usr/*' --output-file coverage.info
   lcov --list coverage.info --output-file coverage.txt
}

compute_coverage