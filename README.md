# Puzzle-a-day-Solver

## Build the C++ Solver

Debug build: 
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

Release build:
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

On Windows:
```
venv\stats_env\Scripts\activate
```

On Linux:
```
source venv/stats_env/bin/activate
```
