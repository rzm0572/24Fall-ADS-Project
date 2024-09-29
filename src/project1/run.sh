cmake -B build
cd build && make $1 && cd ..
./build/$1 data/debug.in
