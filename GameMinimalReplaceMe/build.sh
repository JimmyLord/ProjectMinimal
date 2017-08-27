pushd ../Framework
./build.sh
popd

if [ ! -d "build" ]; then
    mkdir build
    cd build
    cmake ..
fi
cd build
make