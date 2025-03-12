#!/bin/bash
paste -d, $1 $2 > marks3.csv


# Specify the CSV file
csv_file="marks3.csv"
touch temp_marks3.csv   

temp_file="temp_marks3.csv"
>temp_marks3.csv


# Initialize STR for appending
STR=""

# Read each line of the CSV file
while IFS=',' read -r col1 col2 col3 col4
do
    # echo "Column 1 : $col1 , Column 3: $col3"

    # Compare col1 and col3
    if [ "$col1" != "$col3" ]; then
        
        # Set STR for appending to the file
        STR="$col3,-,-,$col4"


        # Change col4 to "-"
        col4="-"
        # echo "Modified Column 4 to: $col4"
        
    fi

    # Write the modified row to the temporary file
    echo "$col1,$col2,$col3,$col4" >> "$temp_file"
done < "$csv_file"

# delete column 3 


# Append STR to the bottom of the CSV file
if [ -n "$STR" ]; then
    echo "$STR" >> "$temp_file"
fi

cp "$temp_file" "$csv_file"

cut -d',' --complement -f3 marks3.csv > temp.csv && mv temp.csv marks3.csv

cat marks3.csv

