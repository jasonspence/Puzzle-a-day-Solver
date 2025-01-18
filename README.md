# Puzzle-a-day-Solver

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