#!/bin/bash
## Jenil_Patel_202101074
## count all files in given path 

path_=$1
if [[ ! $1 ]]; then
    path_=$(pwd)
fi
echo -en "\nNumber of file(s) in \"$path_\" location is/are: "
find ${path_} -type f | wc -l ; echo
