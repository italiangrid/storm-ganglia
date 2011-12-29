#!/bin/sh
# Author: Mario David (david@lip.pt)

gcc -c -fPIC -I /usr/include/apr-1/ ../src/modstorm.c -o ../src/modstorm.o
gcc -shared -Wl,-soname,modstorm.so -o ../src/modstorm.so ../src/modstorm.o
