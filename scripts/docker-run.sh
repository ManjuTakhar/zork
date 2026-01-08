#!/bin/bash

# Docker run script for Zork game

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== Zork Docker Run Script ===${NC}"

# Get project root
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

# Default values
IMAGE_NAME="zork"
IMAGE_TAG="latest"

# Parse arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        --tag)
            IMAGE_TAG="$2"
            shift 2
            ;;
        *)
            echo -e "${YELLOW}Unknown option: $1${NC}"
            shift
            ;;
    esac
done

# Check if image exists
if ! docker image inspect "${IMAGE_NAME}:${IMAGE_TAG}" &> /dev/null; then
    echo -e "${YELLOW}Image not found. Building...${NC}"
    bash "$PROJECT_ROOT/scripts/docker-build.sh" --tag "$IMAGE_TAG"
fi

# Create saves directory if it doesn't exist
mkdir -p "$PROJECT_ROOT/saves"

echo -e "${GREEN}Running Zork in Docker container...${NC}"

# Run container
docker run -it --rm \
    --name zork-game \
    -v "$PROJECT_ROOT/saves:/app/saves" \
    -e TERM=xterm-256color \
    "${IMAGE_NAME}:${IMAGE_TAG}"
