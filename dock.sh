container=dc1a3e1c8c4b

docker cp ./src $container:/bypass/
docker exec -it $container /bin/bash -c "export PYTHONPATH=\"/opt/nest/lib/python3.10/site-packages/:$PYTHONPATH\"; python bypass/src/$1"
docker cp $container:/bypass/pickle_ ./
