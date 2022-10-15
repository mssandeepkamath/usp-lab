#!/bin/bash

echo "Enter the string"
read string
echo "Enter the starting position"
read position
echo "Enter the substring length"
read length
echo ${string:$position:$length}

# Note that string does not have $ whereas position and length as $
# ${} is a variable substitution
# $() or ` ` is a command substitution
# Here string:1:2 is a variable hence variable substitution

