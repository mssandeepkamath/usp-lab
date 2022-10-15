#!/bin/bash

echo "Enter the directory"
read -r dir_name
echo "Enter the permission in rwxrwxrwx format"
read -r permission
content=$(ls -lR $dir_name)
echo "$content" | grep "$permission"

# Do not use -n in echo
# Use -r in read to prevent / acting like EOL
# Do not use any substitutions when we have grep!, just use echo "$" | grep "$"
# Note about how to give a input