#!/bin/bash

echo "Enter the file name"
read file_name
count_lines=$(cat $file_name | wc -l)
echo "$count_lines"

# cat -n <file_name> will give you lines and content
# understand command substitution
# No space should be left between assignment ie. variable=$()
