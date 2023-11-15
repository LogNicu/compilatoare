#!/bin/bash

sshpass -p "fedora_rocks!" scp -P 10000 -r /home/nicu/compilatoare riscv@127.0.0.1:/home/riscv > /dev/null  2>&1
echo "Done!"
