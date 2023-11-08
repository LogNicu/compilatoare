#!/bin/bash

bison -dy my.y && flex my.l &&  g++ -o parser lex.yy.c y.tab.c -lm -lfl 