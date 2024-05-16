#!/bin/bash

if [ $1 -gt $2 ] && [ $1 -gt $3 ]; then
    echo "Your greatest number is: $1"
elif [ $2 -gt $1 ] && [ $2 -gt $3 ]; then
    echo "The greatest number is: $2"
else
    echo "The greatest number is: $3"
fi
