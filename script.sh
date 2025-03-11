#!/bin/bash

# Ensure both files are sorted by 'number' (first column)
sort -t, -k1,1 marks1.csv > sorted_marks1.csv
sort -t, -k1,1 marks2.csv > sorted_marks2.csv

# Use 'join' to merge the files on the 'number' column
join -t, -e "-" -a1 -a2 sorted_marks1.csv sorted_marks2.csv > result.csv

# Show the result
cat result.csv
