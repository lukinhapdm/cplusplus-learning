# graduacao-cpp
 
Code, examples and solved exercises in C++ studied throughout my undergraduate degree, organized by topic.
 
> Code comments and exercise statements are written in Portuguese.
 
## Topics
 
| Folder | Topic |
|---|---|
| 01–10 | Fundamentals: introduction, variables, operators, conditionals, functions, loops, arrays/matrices, strings, structs, files |
| 11 | Abstract data types, pointers and functions |
| 12–14 | Stack, queue and linked lists |
| 15–16 | Binary trees (BST/AVL) and hashing |
| 17 | Sorting algorithms |
| 18–23 | OOP: classes, inheritance, overloading, friend/virtual functions, polymorphism, templates and exceptions |
 
Each folder contains `exemploXX` files (lesson examples) and `exercicioXX` files (commented solutions).
 
## Running in VS Code
 
1. Install the **g++** compiler:
   - **Windows:** [MSYS2](https://www.msys2.org) → in the MSYS2 terminal run `pacman -S mingw-w64-ucrt-x86_64-gcc` and add `C:\msys64\ucrt64\bin` to your PATH.
   - **Linux:** `sudo apt install g++ gdb`
   - **macOS:** `xcode-select --install`
2. Check the installation: `g++ --version`.
3. Open the **repository folder** in VS Code and accept the recommended extensions (C/C++ and Code Runner).
4. Open any `.cpp` file and use one of these options:
   - **Play button (Code Runner)** in the top-right corner → compiles and runs in the terminal.
   - `Ctrl+Shift+P` → *Tasks: Run Task* → **Compilar e executar** (compile and run).
   - **F5** → debug (breakpoints, variable values).
> **Windows:** if the Play button fails with an `&&` error, your terminal is the legacy PowerShell. Use the **Compilar e executar** task (works in any terminal) or switch the default terminal to *Git Bash* / *PowerShell 7*. The task also fixes accented characters in the output.
 
From the terminal: `g++ -std=c++17 file.cpp -o program && ./program`
 
