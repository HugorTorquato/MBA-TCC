# Use Ubuntu as the base image
FROM ubuntu:22.04

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    g++ cmake git libboost-all-dev libasio-dev \
    && rm -rf /var/lib/apt/lists/*
    
# Set the working directory inside the container
WORKDIR /app

# Copy source code and CMakeLists.txt
COPY . .

# Clone a fixed version of Crow (Example: v1.2.1.2)
RUN git clone --branch v1.2.1.2 https://github.com/CrowCpp/Crow.git /includes/Crow
WORKDIR /includes/Crow
# Build Crow
RUN mkdir build
WORKDIR /includes/Crow/build
RUN cmake .. -DBUILD_SHARED_LIBS=ON && make -j$(nproc) && make install



# Set up project
WORKDIR /app
RUN mkdir -p build
WORKDIR /app/build
RUN cmake .. && make -j$(nproc)

# Expose API port
EXPOSE 8080

# Run the API when the container starts
CMD ["./build/api_server"]