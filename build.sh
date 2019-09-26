#!/bin/bash

INCLUDE_DIR='./include'
MODULES='./src'


#compile + build source
gcc -c main.c -I $INCLUDE_DIR $MODULES/*.c
mkdir bin
mv *.o bin

#link sources
gcc -I $INCLUDE_DIR bin/*.o -o magnesium

