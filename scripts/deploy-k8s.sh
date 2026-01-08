#!/bin/bash

# Kubernetes deployment script for Zork game

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}=== Zork Kubernetes Deployment Script ===${NC}"

# Get project root
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
K8S_DIR="$PROJECT_ROOT/kubernetes"

# Check if kubectl is installed
if ! command -v kubectl &> /dev/null; then
    echo -e "${RED}Error: kubectl is not installed${NC}"
    exit 1
fi

# Parse arguments
ACTION="apply"
NAMESPACE="default"

while [[ $# -gt 0 ]]; do
    case $1 in
        --delete)
            ACTION="delete"
            shift
            ;;
        --namespace)
            NAMESPACE="$2"
            shift 2
            ;;
        *)
            echo -e "${YELLOW}Unknown option: $1${NC}"
            shift
            ;;
    esac
done

echo -e "${GREEN}Action: $ACTION${NC}"
echo -e "${GREEN}Namespace: $NAMESPACE${NC}"

# Apply or delete resources
if [ "$ACTION" = "apply" ]; then
    echo -e "${GREEN}Deploying Zork to Kubernetes...${NC}"
    
    kubectl $ACTION -f "$K8S_DIR/configmap.yaml" -n "$NAMESPACE"
    kubectl $ACTION -f "$K8S_DIR/pvc.yaml" -n "$NAMESPACE"
    kubectl $ACTION -f "$K8S_DIR/deployment.yaml" -n "$NAMESPACE"
    
    echo -e "${GREEN}=== Deployment successful! ===${NC}"
    echo -e "${GREEN}Check status with: kubectl get pods -n $NAMESPACE${NC}"
else
    echo -e "${YELLOW}Removing Zork from Kubernetes...${NC}"
    
    kubectl $ACTION -f "$K8S_DIR/deployment.yaml" -n "$NAMESPACE" || true
    kubectl $ACTION -f "$K8S_DIR/pvc.yaml" -n "$NAMESPACE" || true
    kubectl $ACTION -f "$K8S_DIR/configmap.yaml" -n "$NAMESPACE" || true
    
    echo -e "${GREEN}=== Removal complete! ===${NC}"
fi
