#!/bin/bash
chmod +x var.sh
chmod +x print.sh


start_time=$SECONDS

if [[ $# != 1 ]]
then
    echo "Error: number of arguemetns should be 1"
    exit 1
fi

if [[ ! $1 == */ ]]
    then
    echo "Error: at the end of paramater should be /"
    exit 1
fi

if [[ ! -d "$1" ]] 
    then
    echo "Error: doesnt exist"
    exit 1
fi

. ./var.sh
. ./print.sh

end_time=$((SECONDS - start_time))
echo "Script execution time (in seconds) = $end_time"