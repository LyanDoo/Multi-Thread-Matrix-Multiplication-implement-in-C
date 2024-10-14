#!/bin/bash
gcc "$1.c" -o $1 -pthread
echo "exit code: $?"
"./$1"