# Maze Generation with Backtracking

This project implements an algorithm for maze generation using **backtracking techniques**. 
The program is developed in **C** and utilizes a **dynamic stack** to manage coordinates 
during the maze exploration. The maze is drawn and manipulated directly in the console 
using the `conio.h` and `windows.h` libraries.


- Windows Environment
- [MinGW](https://sourceforge.net/projects/mingw/)


### Requisitos
### How to Compile

1. Navigate to the project directory and run the following command to compile:

```bash
gcc interface/interface.c interface/stack/stack.c main.c -o main.exe
```
2. To execute the program:

```bash
.\main.exe
```
###

## Execution Preview

---

<img src="/images/execution.gif">

## Features

- **Maze Generation:** Implements the backtracking algorithm to create random mazes.
- **Stack Management:** Utilizes a dynamic stack to handle coordinates during exploration.
- **Console Visualization:** The generated maze is displayed in the console, along with additional information such as stack state and maze settings.
- **Customizable Settings:** Users can modify maze dimensions, drawing colors, and other parameters.

### Components

### Stack Functions

The following functions manage the dynamic stack:

- **allocate_sequential_list:** Dynamically allocates a sequential list with an initial capacity.
- **increase_list_capacity:** Increases the capacity of the sequential list when necessary.
- **decrease_list_capacity:** Reduces the capacity of the sequential list when unused space is detected.
- **insert_coordinate:** Inserts a coordinate into the sequential list, resizing it if needed.
- **remove_coordinate:** Removes the most recent coordinate from the list and adjusts its capacity.
- **free_sequential_list:** Releases the memory allocated for the sequential list.

### Memory Allocations
- **Sequential List:** Dynamically allocated to store explored coordinates, with capacity adjusted during maze exploration.
- **Maze Matrix:** Dynamically allocated based on user-defined dimensions (height and width).
