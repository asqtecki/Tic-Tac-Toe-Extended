# Tic-Tac-Toe-Extended
GUI based two-player Tic Tac Toe written in C++ using Raylib.

## Features
* Button class that can be used to create a custom menu.
* GUI Based.
* Automated win/draw detection.
* Game restarts after each round.

## Pre-requisites
Before compiling, ensure you have the following installed: 
* **Raylib**: Game development library for C/C++.
* **Assets**: The "Graphics/" folder containing 'start.png' and 'bg.jpg'.
* **w64devkit (MinGW-w64)**: The 64-bit compiler included with the raylib installer.

## Compilation and Setup
Type the following commands on your Command Prompt OR Terminal once the Pre-requisites are installed and set up.

* Clone the repository:
```cmd
git clone https://github.com/asqtecki/Tic-Tac-Toe-Extended.git
```
* Navigate to the folder (Say Desktop/Tic-Tac-Toe-Extended):
```cmd
cd Desktop/Tic-Tac-Toe-Extended
```

* To ensure the 64-bit compiler is used and to avoid architecture conflicts:
```cmd
set PATH=C:\raylib\w64devkit\bin;%PATH%
```

* Compile the source (Raylib must be installed in the given path): 
```cmd
g++ main.cpp -o tictactoe.exe -I C:/raylib/raylib/src -L C:/raylib/raylib/src -lraylib -lopengl32 -lgdi32 -lwinmm -static
```

* Execute
```cmd
tictactoe
```
OR
```
tictactoe.exe
```

## How to Play
* Once executed, click the start button to start the round.
* Use the left mouse button to interact with the board and mark it with X and O.
* The game automatically detects a win or a draw.
* After a round concludes, the game takes one back to the home screen where they can click the start button to launch another round.

## Implementation details
* **Object-oriented Approach**: Uses a **Board** class and a **Button** class for game state and UI interactions, respectively.
* **Memory Management**: Textures are unloaded using class destructors.
* **Input Detection**: Uses *CheckCollisionPointRec* to detect mouse inputs.


