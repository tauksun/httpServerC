containerImage="http-server-c-image"
containerName="http-server-c"

echo -e "\nCleaning previous build..."
make clean

echo -e "\nCreating new build..."
make

oldContainerId=$(sudo docker ps -aqf "name=$containerName")
echo -e "\nOld container id : $oldContainerId"

# Remove previous container on new deployment
if [ $oldContainerId ]
then
    echo -e "\nRemoving previous container : $oldContainerId\n"
    sudo docker rm -f -v $oldContainerId
fi

echo -e "\nBuilding image..."
sudo docker build -t $containerImage .

echo -e "\nStarting container..."
sudo docker run --name $containerName -d --network=host --restart=on-failure $containerImage
