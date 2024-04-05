#!/bin/bash

gcc -fPIC -fno-stack-protector -c src/main.c

sudo ld -x --shared -o /usr/lib/x86_64-linux-gnu/security/pam-group112.so main.o

rm main.o
