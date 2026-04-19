if [ "$1" = "-clean" ]; then
  rm -rf build
  mkdir build
fi

mkdir build

cmake -S . -B build
cmake --build build

./build/WRender

