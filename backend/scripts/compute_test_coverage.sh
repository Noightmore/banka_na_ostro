#!/bin/bash

# This script computes the test coverage of the codebase.

function compute_coverage()
{
   llvm-profdata merge -sparse default.profraw -o default.profdata
   llvm-cov show backend.cgi -instr-profile=default.profdata
}

compute_coverage