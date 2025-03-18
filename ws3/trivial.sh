#!/bin/bash
set -- "hello" "$1"



i=1
for var in "$@"; do
    echo "$i= $var"
    ((i++))
done
