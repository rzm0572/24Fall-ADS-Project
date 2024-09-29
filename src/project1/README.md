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
   └─ dataGen.cpp
```

## Usage

You need to have `cmake` and `make` installed on your system.

There're three algorithms implemented: baseline, AVL and splay. To build and run one of the algorithms, run the following commands:

```bash
./run.sh <algorithm_name>
```

To modify the input data, you can modify `run.sh` to point to a different input file.
