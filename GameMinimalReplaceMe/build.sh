
if [[ ! $1 =~ ^(Debug|Release|wxDebug|wxRelease)$ ]]; then
    echo "Specify a build configuration: Debug, Release, wxDebug, wxRelease"
    exit 2
fi

BuildConfiguration="$1"

echo "========== Configuration: $BuildConfiguration =========="

pushd ../Framework > /dev/null
    ./build.sh $BuildConfiguration
popd > /dev/null

echo "========== Building MinimalReplaceMe =========="

if [ ! -d "build" ]; then
    mkdir build
fi

if [ ! -d build/$BuildConfiguration ]; then
    mkdir build/$BuildConfiguration
    pushd build/$BuildConfiguration > /dev/null
        cmake -DCMAKE_BUILD_TYPE=$BuildConfiguration ../..
    popd > /dev/null
fi

pushd build/$BuildConfiguration > /dev/null
make
popd > /dev/null
