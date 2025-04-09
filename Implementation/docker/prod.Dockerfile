FROM ubuntu:22.04

# Install runtime-only dependencies
RUN apt-get update && apt-get install -y \
    libboost-all-dev libasio-dev \
    && rm -rf /var/lib/apt/lists/*

COPY build/api_server /app/api_server

WORKDIR /app
EXPOSE 8080
CMD ["./api_server"]