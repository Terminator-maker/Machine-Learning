Maze Traversal Simulator (DFS and BFS)

Overview

This is a console-based $\text{C++}$ application that visualizes the Depth First Search (DFS) and Breadth-First Search (BFS) algorithms solving a dynamically generated 25x25 maze in real-time. The application requires Windows to function, as it uses specific headers (windows.h, MMsystem.h) for colored text, animated cursor positioning, and background music playback.

Features

This program offers real-time visualization of mouse traversal ('X') using either DFS (Stack-based) or BFS (Queue-based). A new maze is generated for every run, and custom console colors are used to distinguish the walls, explored paths, and the green Exit ('E').

Prerequisites

To compile and run this program, you need:

A C++ Compiler: $\text{GCC}$ (via MinGW or Cygwin) is recommended.

Windows Operating System: Required for the console and multimedia functions.

Audio File: The file Undertale OST - 059 Spider Dance.wav must be located in the same directory as the executable (main.exe).

Building the Project

The Windows Multimedia library must be linked during compilation.

Compilation Command

Use the following command, ensuring you include the -lwinmm flag:

g++ main.cpp -o main.exe -lwinmm


Component

Description

g++

The $\text{C++}$ compiler.

main.cpp

The primary source code file.

-o main.exe

Specifies the output filename as main.exe.

-lwinmm

CRITICAL: Links the Windows Multimedia library (required for PlaySound).

Running the Executable

Ensure the .wav file is present, then execute the program directly in $\text{CMD}$ or $\text{PowerShell}$:

.\main.exe


Program Controls

Select 1 for DFS (Stack) or 2 for BFS (Queue).

The visualization starts immediately.

Press any key after the "escaped the Maze!" message to return to the menu.

Select 3 to exit.