#!/bin/bash

if [ $1 -gt $2 ]; then
    echo "The greatest number is: $1"
elif [ $2 -gt $1 ]; then
    echo "The greatest number is: $2"
else
    echo "Both numbers are equal."
fi
