FROM mcr.microsoft.com/vscode/devcontainers/base:0-ubuntu-22.04

RUN sudo apt -y update && \
    sudo apt -y install build-essential pkg-config gdb

# Download and extract CMake
RUN sudo wget https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-linux-x86_64.tar.gz && \
    sudo tar -zxvf cmake-3.31.5-linux-x86_64.tar.gz && \
    sudo mv cmake-3.31.5-linux-x86_64 /opt/cmake-3.27

# Set CMake binary path
ENV PATH="/opt/cmake-3.27/bin:${PATH}"

# Verify installation
RUN cmake --version
