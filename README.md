# Puzzle-a-day-Solver

## Overview

This project enumerates and analyzes all solutions to a tetris-like game called "A-Puzzle-A-Day" by Dragon Fjord Puzzles.  I am not associated with the creators of the puzzle.

The puzzle is played on a grid of 43 squares, each labelled with either a month or a day from 1 to 31. 

![Empty puzzle board](https://github.com/user-attachments/assets/9a4c4399-6d37-477d-9f81-437d16a4cf58)

8 tetronimo-like pieces are given to tile the game board, covering a total of 41 squares collectively.

![8 unique puzzle pieces](https://github.com/user-attachments/assets/4995b9e9-dac1-48eb-86c3-fed759a340da)

The puzzle objective is to pre-select two positions that spell out the current date, and then to find a position for the 8 tetronimos to cover all squares except those two designated squares that spell the date.  The following image displays a solution for January 18th. 

![Solved puzzle board for January 18](https://github.com/user-attachments/assets/300e5ce7-b486-44a7-879a-1b3496dc9ebb)

After solving several daily puzzles, and finding that my friend's solutions often differred from my own, I decided to find out just how many solutions there are for any given day.  

**This project contains both the data for all solutions and the code necessary to recompute the values** or to change and compute the results of a similar game of your choosing.

## Methods

> Note: instructions to compile and run the solver yourself are below the Data & Results

I used C++ compiled with cmake and ninja to produce the list of all possible solutions.  I used a "backtracking" depth-first-search algorithm inspired by Sudoku solvers to test each puzzle piece in each possible position and orientation, only attempting to place a puzzle piece after the previous piece has been successfully placed, and backtracking once all positions have been tried, so that the previous piece may be moved to its next available position and the process repeated.  

Once compiled, the Solver program can be run for a single date `build/bin/Solver Jan 18` or unspecified `build/bin/Solver` to produce all possible solutions.  The program reports solutions as they are found in the commandline, and at the end outputs a CSV of found solutions indexed on the two squares left uncovered.  Running the Solver on a single date takes seconds to find a solution, and between 3 and 10 minutes to find all solutions depending on the date.  Running the solver to find all solutions takes nearly an hour, but only ever has to be run once.  Afterwards, it is much more efficient to store the CSV and filter for solutions for a single day. 

To analyze the data, I used Python 3 with Pandas for efficient data handling, and matplotlib to generate plots.  The `analysis.py` script displays several plots, and outputs two new summary CSVs: the number of solutions for each pair of uncovered squares, and the number of solutions for date-like pairs only (those of the form Month/Day, rather than Month/Month or Day/Day). 

## Data & Results

The solver discovered **59,787** unique solutions across `43 choose 2 =` **903** pairs of uncovered squares.  I was right, there are a lot more than one solution per daily puzzle, at least on average.  The pair with the most solutions was January/July with **305** unique solutions, while the valid date with the most solutions was January/25 with **216** unique solutions.  On the other hand, the hardest daily puzzle is October/6 with only **7** unique solutions, while the pair with the fewest solutions was 6/12 with only **1** solution!  There are 7 pairs that have no solutions, which I added manually to the dataset.  

I made a histogram of the number of unique solutions, showing how many puzzle boards have that number of solutions. The bulk of the choices of pairs of points have between 25 and 85 solutions, but they have a wide distribution. 

![Histogram of the frequency of puzzle boards with each number of solutions](https://github.com/user-attachments/assets/5cd2be6c-a4ec-4a2b-aafb-a45eeeed05cb)

I made a heatmap of the number of solutions that are associated with each square on the board.  Note that corners are not disruptive, and provide many solutions, while squares next to corners tend to generate highly constrained areas, reducing the number of possible solutions.  That said, even the most constrained square has over 1000 solutions.

![Heatmap in the shape of the puzzle board, showing the numbers of solutions that do not cover that square](https://github.com/user-attachments/assets/124d3d0b-aa47-434a-9b9f-65f2f0a2719a)

After looking through several solutions, I noticed trends of solutions that only differ in the position of two puzzle pieces.  When the switching of two puzzle pieces results in an identical board solution, that is, leaving the same two squares uncovered, it is due to an aggregate symmetry formed by combining two pieces together.  Two are shown in the next figure.  In the future, I would like to measure greater distances between solutions, to uncover symmetric triplets, for example, or to display a network between solutions.

![Pairs of puzzle pieces that together create symmetrical aggregate shapes](https://github.com/user-attachments/assets/530a1cf3-0093-4a25-98dd-6915581fc8bd)

## Build the C++ Solver

From the workspace directory, run:

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

Display the game board from a solution specification (currently the game board is only shown during the initial C++ generation of solutions).

Make heatmaps for each piece.

Calculate distance between solutions - how many pieces need to move?  Remember that x-motion, y-motion and rotation of a piece are all together still only one move.

Interactive game board with running stats:
- How many solutions are left given the already-placed pieces
- What dates are still available
- Is this a valid move for a particular date
- Minimum number of pieces to move from the current solution to a solution for the next day
