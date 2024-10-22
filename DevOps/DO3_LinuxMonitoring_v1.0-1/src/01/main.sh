#!/bin/bash

if [[ $# != 1 ]]
then
    echo "This script support only 1 parameter"
    exit 1
fi

chmod 777 check.sh
 ./check.sh "$1"
 if [ $? -eq 1 ]; then
     echo "$1"
else
echo "Wrong input"
fi
