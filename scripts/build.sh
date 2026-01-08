#!/bin/bash

# Build script for Zork game

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== Zork Build Script ===${NC}"

# Check if CMake is installed
if ! command -v cmake &> /dev/null; then
    echo -e "${RED}Error: CMake is not installed${NC}"
    exit 1
fi

# Check if compiler is available
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo -e "${RED}Error: No C++ compiler found${NC}"
    exit 1
fi

# Parse arguments
BUILD_TYPE="Release"
CLEAN_BUILD=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --clean)
            CLEAN_BUILD=true
            shift
            ;;
        *)
            echo -e "${YELLOW}Unknown option: $1${NC}"
            shift
            ;;
    esac
done

# Get project root
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build"

echo -e "${GREEN}Project root: $PROJECT_ROOT${NC}"
echo -e "${GREEN}Build type: $BUILD_TYPE${NC}"

# Clean build if requested
if [ "$CLEAN_BUILD" = true ]; then
    echo -e "${YELLOW}Cleaning build directory...${NC}"
    rm -rf "$BUILD_DIR"
fi

# Create build directory
mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure
echo -e "${GREEN}Configuring project...${NC}"
cmake -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..

# Build
echo -e "${GREEN}Building project...${NC}"
make -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

# Check if build was successful
if [ -f "$BUILD_DIR/zork" ]; then
    echo -e "${GREEN}=== Build successful! ===${NC}"
    echo -e "${GREEN}Executable: $BUILD_DIR/zork${NC}"
    echo -e "${GREEN}Run with: $BUILD_DIR/zork${NC}"
else
    echo -e "${RED}=== Build failed! ===${NC}"
    exit 1
fi
