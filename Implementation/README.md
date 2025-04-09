

6️⃣ Running Everything
Now, let’s build and run the API inside Docker.

6.1: Build the Docker Image
    docker build -t cpp-api .
6.2: Run the Container
    docker run -p 8080:8080 cpp-api
Now, your API is running inside a Docker container on port 8080.



docker-compose build -d 

docker-compose up

docker-compose down

1️⃣ Build & Start Container
sh
Copy
Edit
docker-compose up --build
2️⃣ Manually Rebuild (if needed)
sh
Copy
Edit
docker exec -it cpp-api-dev bash
cd build && cmake .. && make -j$(nproc)
./api_server  # Run manually
3️⃣ Stop Container
sh
Copy
Edit
docker-compose down