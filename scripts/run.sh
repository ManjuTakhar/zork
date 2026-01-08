#!/bin/bash

# Run script for Zork game

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Get project root
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"
EXECUTABLE="$BUILD_DIR/zork"

echo -e "${GREEN}=== Zork Run Script ===${NC}"

# Check if executable exists
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${YELLOW}Executable not found. Building...${NC}"
    bash "$PROJECT_ROOT/scripts/build.sh"
fi

# Check again after potential build
if [ ! -f "$EXECUTABLE" ]; then
    echo -e "${RED}Error: Could not find or build executable${NC}"
    exit 1
fi

# Create saves directory if it doesn't exist
mkdir -p "$PROJECT_ROOT/saves"

# Run the game
echo -e "${GREEN}Starting Zork...${NC}"
cd "$PROJECT_ROOT"
"$EXECUTABLE"
