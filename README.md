# 🌀 Maze Generation with Backtracking

This project implements an algorithm for maze generation using **backtracking techniques**. 
The program is developed in **C** and utilizes a **dynamic stack** to manage coordinates 
during the maze exploration. The maze is drawn and manipulated directly in the console 
using the `conio.h` and `windows.h` libraries.


- Windows Environment
- [MinGW](https://sourceforge.net/projects/mingw/)


### Requirements
### How to Compile

1. Navigate to the project directory and run the following command to compile:

```bash
gcc interface/interface.c interface/stack/stack.c main.c -o main.exe
```
2. To execute the program:

```bash
main.exe
```
###

## 🎮 Execution Preview

<img src="/images/maze_drawing.gif">

## 📝 Algorithm

1. Randomly visiting unvisited neighbors from the current cell.
2. Backtracking when no unvisited neighbors are available.
3. Using a dynamic stack to track and revisit paths as needed.

## 📂 Components

### Dynamic Stack Functions

The dynamic stack is the core data structure for managing the exploration process:

- **`allocate_sequential_list`**: Allocates a sequential list with an initial capacity.
- **`increase_list_capacity`**: Expands the list dynamically as needed.
- **`decrease_list_capacity`**: Shrinks the list when unused space is detected.
- **`insert_coordinate`**: Adds a coordinate to the stack, resizing if necessary.
- **`remove_coordinate`**: Removes the top coordinate from the stack.
- **`free_sequential_list`**: Frees memory allocated to the stack.

### Memory Allocations

- **Sequential List**: Dynamically adjusts to store coordinates during backtracking.
- **Maze Matrix**: Allocated based on user-defined dimensions (height and width).
