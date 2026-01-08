#!/bin/bash

# Docker build script for Zork game

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== Zork Docker Build Script ===${NC}"

# Get project root
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$PROJECT_ROOT"

# Default values
IMAGE_NAME="zork"
IMAGE_TAG="latest"
NO_CACHE=false

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --tag)
            IMAGE_TAG="$2"
            shift 2
            ;;
        --no-cache)
            NO_CACHE=true
            shift
            ;;
        *)
            echo -e "${YELLOW}Unknown option: $1${NC}"
            shift
            ;;
    esac
done

# Build command
DOCKER_CMD="docker build"
if [ "$NO_CACHE" = true ]; then
    DOCKER_CMD="$DOCKER_CMD --no-cache"
fi
DOCKER_CMD="$DOCKER_CMD -t ${IMAGE_NAME}:${IMAGE_TAG} ."

echo -e "${GREEN}Building Docker image: ${IMAGE_NAME}:${IMAGE_TAG}${NC}"
echo -e "${GREEN}Command: $DOCKER_CMD${NC}"

# Build image
eval $DOCKER_CMD

if [ $? -eq 0 ]; then
    echo -e "${GREEN}=== Docker image built successfully! ===${NC}"
    echo -e "${GREEN}Image: ${IMAGE_NAME}:${IMAGE_TAG}${NC}"
    echo -e "${GREEN}Run with: docker run -it ${IMAGE_NAME}:${IMAGE_TAG}${NC}"
else
    echo -e "${RED}=== Docker build failed! ===${NC}"
    exit 1
fi
