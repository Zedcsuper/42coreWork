#!/bin/bash

for file in $(find . -type f -name "*.c"); do

	vim -c ":Stdheader" -c ":wq" "$file"
done
