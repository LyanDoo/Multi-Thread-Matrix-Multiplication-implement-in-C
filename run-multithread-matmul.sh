#!/bin/bash
gcc "multithread-matmul.c" -o multithread-matmul -pthread
echo "Running multi thread matrix multiplication"
time "./multithread-matmul"