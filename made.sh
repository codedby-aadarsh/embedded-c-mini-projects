#!/bin/bash
# Check if the argument passed is "wokwi"
if [ "$1" == "wokwi" ]; then
    echo "[wokwi]
version=1
elf=''
firmware=''
" > wokwi.toml
fi

# Check if the argument passed is "diagram"
if [ "$1" == "diagram" ]; then
    nano diagram.json
fi

exit 0
