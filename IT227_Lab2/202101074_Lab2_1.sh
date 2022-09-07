#!/bin/bash
## Jenil_Patel_202101074
## Sum of CLA only upto args

if [[ $# -gt 9 ]]; then
    echo -e "\nMore than 9 arguments! Not accepted.\n"
    exit
fi

sum=0
for i in $@
do
	sum=$[$sum + $i]
done
echo -e "\nSum of all $# command line integer arguments is: ${sum}\n"