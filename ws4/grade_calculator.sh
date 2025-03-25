#!/bin/bash

case $1 in
    9[0-9]|100)  # Matches numbers from 90 to 100
        echo "A"
        ;;
    80|8[1-9])  # Matches 80-89
        echo "B"
        ;;
    70|7[1-9])  # Matches 70-79
        echo "C"
        ;;
    60|6[1-9])  # Matches 60-69
        echo "D"
        ;;
    0|5[1-9])  # Matches 50-59
        echo "F"
        ;;
    *)
        echo "else"
        ;;
esac
