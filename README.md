# Puzzle-a-day-Solver

## Overview

This project enumerates and analyzes all solutions to a tetris-like game.

## Build the C++ Solver

### Debug build: 
```
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Debug ../
ninja
```
or
```
cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
ninja -C build
```

### Release build:
```
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_BUILD_TYPE=Release ../
ninja
```
or
```
cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
-C build
```

## Run the C++ Solver

From the build folder, run:
```
bin/Solver
```
or
```
bin/Solver Mar 7
```

Output data is stored in `output/data.csv`.

## Set up Python environment

From the workspace directory, run:

### On Linux:
```
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
```

### On Windows Bash:
```
python3 -m venv venv
source venv/Scripts/activate
pip install -r requirements.txt
```

## Run the Python analyzer

From the workspace directory, run:

```
python analysis.py
```



## Ideas for future

Make heatmaps for each piece

Calculate distance between solutions - how many pieces need to move?

Interactive game board with running stats
- How many solutions are left given the already-placed pieces
- What dates are still available
- Is this a valid move for a particular date
- Minimum number of pieces to move from the current solution to a solution for the next day
