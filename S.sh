#!/bin/bash

gcc -o exe progc/S.c
res=$(cut -f1,5 "data/$1" > ./exe)
