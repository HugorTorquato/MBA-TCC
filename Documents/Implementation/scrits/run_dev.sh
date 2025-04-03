#!/bin/bash

cd ..

# Stop existing container
docker-compose down

# Start container in background
docker-compose up --build -d

# # Attach to logs (optional)
# docker logs -f cpp-api-dev
