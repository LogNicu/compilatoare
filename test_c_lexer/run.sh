#!/bin/bash

flex -o ${1}.c ${1}.l

gcc ${1}.c -o ${1}

./${1} < ${2}

rm ${1}.c
rm ${1}
