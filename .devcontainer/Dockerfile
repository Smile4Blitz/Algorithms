FROM mcr.microsoft.com/vscode/devcontainers/base:0-ubuntu-22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN sudo apt update -y && \
    sudo apt install -y --no-install-recommends build-essential pkg-config gdb && \
    sudo apt clean && sudo rm -rf /var/lib/apt/lists/*

COPY ./cmake-3.31.5-linux-x86_64.tar.gz /tmp/

RUN sudo tar -zxvf /tmp/cmake-3.31.5-linux-x86_64.tar.gz -C /opt && \
    sudo mv /opt/cmake-3.31.5-linux-x86_64 /opt/cmake-3.27 && \
    rm /tmp/cmake-3.31.5-linux-x86_64.tar.gz

ENV PATH="/opt/cmake-3.27/bin:${PATH}"
RUN cmake --version