#!/bin/bash

# Change to the build directory
cd "$(dirname "$0")/Build" || exit 1

# Rebuild (optional): Uncomment if you want to rebuild every time
# cmake ..
# make -j$(nproc)
#
if [ ! -f "$EXECUTABLE_NAME" ]; then
    echo "Building project..."
    cmake .. && make -j$(nproc)
fi


EXECUTABLE_NAME="GameEngine"

GREEN='\033[0;32m'
NC='\033[0m' 

# Run the executable
if [[ -x "$EXECUTABLE_NAME" ]]; then
    echo -e "${GREEN}Launching game engine...${NC}"
    ./"$EXECUTABLE_NAME" "$@"
else
    echo "Executable '$EXECUTABLE_NAME' not found or not executable."
    echo "You may need to build it with cmake and make."
    exit 1
fi

