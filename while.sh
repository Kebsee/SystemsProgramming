#!bin/bash/
num="2";
num=$((num))
str="ABCDEFGHIJKLMNOPQRSTUVWXYZ"

echo"$(str:$num:1)"

# echo "ABCDEFGHIJKLMNOPQRSTUVWXYZ" | tr '[A-Z]' '[B-ZA-B]'
