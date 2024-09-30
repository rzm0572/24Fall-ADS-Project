cmake -B build
cd build && make $1 && cd ..
./build/$1 data/data_random_10000.in
