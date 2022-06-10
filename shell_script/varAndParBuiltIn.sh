#!/bin/sh
salutation="Hello"
echo $salutation
echo "Now execute the program $0"
echo "The second paramater is $2"
echo "The first paramater is $1"
echo "The list of parameters is $*"
echo "The home directory is $HOME"

echo "Insert the new salutation"
read salutation
echo $salutation
echo "Script end"
exit 0