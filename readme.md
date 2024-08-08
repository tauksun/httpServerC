# Run on Local

## Run as container

     sudo docker run --name c-http-server -d -p 5454:5454 tauksun/c-http-server

## Build from source

     bash ./runOnLocal.sh
     visit : localhost:5454

# Build & run as container

    bash ./containerize.sh

# Details

     Running port & number of threads are defined in constants
