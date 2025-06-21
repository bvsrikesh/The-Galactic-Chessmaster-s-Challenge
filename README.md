# Quantum ChessBoard & Closest Pair Analyzer

This project implements two powerful, algorithmically rich modules in C++:
- A **Quantum ChessBoard** engine supporting real-time matrix operations
- A **Closest Pair Finder** based on efficient divide-and-conquer strategy in 2D space

The system is interactive and operates via structured command inputs, enabling dynamic sorting, inversion analysis, and geometric proximity queries over integer coordinate sets.

## 🔍 Features

### 🧮 Quantum ChessBoard Module
- **Custom Row-wise Sorting:**  
  Each row of the board is independently sorted using a stable merge sort, configurable in ascending or descending order via a comparator class.
- **Global Inversion Counting:**  
  Efficiently flattens the 2D matrix into 1D and uses merge sort to count the number of inversion pairs (i.e., disorderings) in `O(n log n)` time.
- **Matrix Display Utility:**  
  Supports printing the current state of the board at any time for verification or debugging.

### 📐 Closest Pair Module
- **Divide-and-Conquer Closest Pair Algorithm:**  
  Finds the pair of points with the smallest Euclidean distance in `O(n log n)` time by recursively splitting and conquering across the X-axis and resolving ties lexicographically.
- **Robust Tie-Breaking Logic:**  
  Ensures that if multiple pairs have the same minimum distance, the lexicographically smallest one (by x, then y) is returned.
- **Brute Force Fallback:**  
  For small subsets, falls back to a brute-force algorithm to maintain correctness.

## 📦 Commands Supported

| Command       | Description                                             |
|---------------|---------------------------------------------------------|
| `CREATE_2D`   | Initializes and inputs the board of size `n x n`        |
| `SORT_2D asc|desc` | Sorts each row in ascending or descending order     |
| `INVERSION_2D`| Counts the number of inversions in the entire matrix    |
| `DISPLAY_2D`  | Prints the current matrix state                         |
| `CLOSEST_2D`  | Reads `n` 2D points and finds the closest pair          |
| `END`         | Terminates the session                                  |

## 🛠️ Compilation

```bash
g++ -std=c++17 -o quantum_solver Solution.cpp
./quantum_solver

