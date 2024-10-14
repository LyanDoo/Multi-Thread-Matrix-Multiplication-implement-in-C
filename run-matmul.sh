#!/bin/bash
gcc "matrix-mul.c" -o matrix-mul
echo "Running multi thread matrix multiplication"
time "./matrix-mul"