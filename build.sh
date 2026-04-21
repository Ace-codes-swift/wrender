if [ "$1" = "-clean" ]; then
  rm -rf build
fi

mkdir -p build

cmake -S . -B build
cmake --build build

./build/WRender

