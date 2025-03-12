#!/bin/bash

if [ "$#" -lt 2 ]; then
    echo "Usage: $0 file1.csv file2.csv [file3.csv ...]"
    exit 1
fi

# Extract headers from each file
header="number"
temp_files=()

for file in "$@"; do
    col_name=$(head -n 1 "$file" | cut -d',' -f2)  # Extract column header
    header+=",${col_name}"
    
    # Extract and sort data (excluding the header)
    tail -n +2 "$file" | sort -t',' -k1,1 > "${file}.sorted"
    temp_files+=("${file}.sorted")
done

# Get a sorted list of all student numbers
cut -d',' -f1 "${temp_files[@]}" | sort -u > all_students.txt

# Merge marks using `join`
merged="all_students.txt"
for sorted_file in "${temp_files[@]}"; do
    join -t',' -a1 -a2 -e'-' -o auto "$merged" "$sorted_file" > merged_temp.txt
    mv merged_temp.txt "$merged"
done

# Print final output
echo "$header"
cat "$merged"

# Cleanup temporary files
rm -f all_students.txt "${temp_files[@]}"
