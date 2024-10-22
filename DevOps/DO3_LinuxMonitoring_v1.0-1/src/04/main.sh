#!/bin/bash

chmod +x print.sh
chmod +x var.sh
chmod +x colour.sh
chmod +x colours.conf

. ./colour.sh
if [[ $# != 0 ]]
then
echo "Error: number of arguemetns should be 0"
exit 1
fi
while IFS='=' read _ value
do
    if [[ ! $value =~ ^[1-6]$ ]] && [[ -n $value ]]
    then
    echo "Error: arguments can take values from 1 to 6"
    exit 1
    fi
done < colours.conf
if [ $color_name_back1 == $color_name_font1 ] || [ $color_name_back2 == $color_name_font2 ]
then
    echo "Еrror: background and text colors cannot be the same"
    exit 1
fi 

. ./colour.sh  
. ./var.sh
. ./print.sh