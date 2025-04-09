# Use Ubuntu as the base image
FROM ubuntu:22.04 

# Install build dependencies
RUN apt-get update && apt-get install -y \
    g++ cmake git libboost-all-dev libasio-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# Install Crow
RUN git clone --branch v1.2.1.2 https://github.com/CrowCpp/Crow.git /includes/Crow \
    && cd /includes/Crow && mkdir build && cd build \
    && cmake .. -DBUILD_SHARED_LIBS=ON && make -j$(nproc) && make install

# Install googletest
RUN git clone https://github.com/google/googletest.git /tmp/googletest && \
    cd /tmp/googletest && \
    cmake -S . -B build && \
    cmake --build build -j$(nproc) && \
    cmake --install build && \
    rm -rf /tmp/googletest

WORKDIR /app