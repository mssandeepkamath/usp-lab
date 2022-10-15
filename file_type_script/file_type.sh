#!/bin/bash

echo "Enter the file name"
read file_name
if [ -d $file_name ]
then
echo "$file_name is a Directory file"
elif [ -L $file_name ]
then
echo "$file_name is a Symbolic link file"
elif [ -f $file_name ]
then
echo "$file_name is a Regular file"
elif [ -b $file_name ]
then
echo "$file_name is a Block device file"
elif [ -c $file_name ]
then 
echo "$file_name is a Character device file"
else
echo "$file_name does not exist"
fi
 
# Problems:
# Note the indentation
# Note the shebang
# Place regular file at last
# Note that for symbolic file its -L, regukar file -f
# Note about creating different types of files
# ln -s [source/existing] [destination/new] 
# After creating, new->existing
# sudo su - for root privilage
# mknod <file_name> <c/b> 89 1