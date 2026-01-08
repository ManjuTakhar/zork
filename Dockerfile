# Multi-stage build for optimized image size
FROM gcc:12 AS builder

# Install CMake and build dependencies
RUN apt-get update && apt-get install -y \
    cmake \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Create build directory and build the project
RUN mkdir -p build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make -j$(nproc)

# Runtime stage
FROM ubuntu:22.04

# Install runtime dependencies
RUN apt-get update && apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

# Create non-root user for security
RUN useradd -m -u 1000 zork && \
    mkdir -p /app/saves && \
    chown -R zork:zork /app

# Set working directory
WORKDIR /app

# Copy binary from builder
COPY --from=builder /app/build/zork /app/zork
COPY --from=builder /app/data /app/data

# Switch to non-root user
USER zork

# Expose any ports if needed (not required for text-based game)
# EXPOSE 8080

# Set environment variables
ENV ZORK_SAVE_DIR=/app/saves

# Health check (optional)
HEALTHCHECK --interval=30s --timeout=3s --start-period=5s --retries=3 \
    CMD ps aux | grep -v grep | grep zork || exit 1

# Run the game
ENTRYPOINT ["/app/zork"]
CMD []
