# Project 1: Binary Search Trees

## Project Structure

```
project1
├─ CMakeLists.txt
├─ README.md
├─ data
│  └─ debug.in
├─ include
│  └─ BST.h
├─ run.sh
├─ src
│  ├─ AVL.cpp
│  ├─ baseline.cpp
│  ├─ main.cpp
│  └─ splay.cpp
└─ utils
   ├─ autobench.py
   └─ dataGen.py
```

## Building and Running

You need to have `cmake` and `make` installed on your system.

There're three algorithms implemented: baseline, AVL and splay. To build and run one of the algorithms, run the following commands in the project directory:

```bash
./run.sh <algorithm_name>
```

To modify the input data, you can modify `run.sh` to point to a different input file.

## Testing

To test the performance of these algorithms, you can use the `autobench.py` script. The steps to test are:

1. Make sure you have `python3` installed and `numpy` and `matplotlib` packages installed. You can install them using `pip3 install numpy matplotlib`.

2. Build the project.
   
3. Generate input data using `dataGen.py`: Run `python3 utils/dataGen.py` in the project directory.

4. Run the `autobench.py` script: Run `python3 utils/autobench.py` in the project directory, and the script will run the algorithms on the input data and output the results in `result` directory.
