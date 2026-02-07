#!/bin/bash

SRC=turbo.c

gcc -O3 $SRC -o turbo -lm
gcc -O3 -march=native $SRC -o turbo2 -lm
gcc -O3 -march=native -mtune=native -funroll-loops $SRC -o turbo3 -lm
gcc -O3 -march=native -flto $SRC -o turbo4 -lm
gcc -O3 -march=native -flto -fno-trapping-math -fno-math-errno $SRC -o turbo5 -lm
