# graduacao-cpp
 
Code, examples and solved exercises in C++ studied throughout my undergraduate degree, organized by topic.
 
> Code comments and exercise statements are written in Portuguese.
 
## Topics
 
| Folder | Topic | Course |
|---|---|---|
| 01–10 | Fundamentals: introduction, variables, operators, conditionals, functions, loops, arrays/matrices, strings, structs, files | ![LP](https://img.shields.io/badge/L%C3%93GICA%20DE%20PROGRAMA%C3%87%C3%83O-2ea043?style=flat-square) |
| 11 | Abstract data types, pointers and functions | ![AED I](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20I-1f6feb?style=flat-square) |
| 12–14 | Stack, queue and linked lists | ![AED I](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20I-1f6feb?style=flat-square) |
| 15–16 | Binary trees (BST/AVL) and hashing | ![AED I](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20I-1f6feb?style=flat-square) |
| 17 | Sorting algorithms | ![AED I](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20I-1f6feb?style=flat-square) |
| 18–23 | OOP: classes, inheritance, overloading, friend/virtual functions, polymorphism, templates and exceptions | ![AED I](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20I-1f6feb?style=flat-square) |
| 24–25 | Searching: sequential and binary search, hashing | ![AED II](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20II-8250df?style=flat-square) |
| 26–29 | Binary search trees, templates and STL, tree balancing (binary-search technique, DSW), AVL trees | ![AED II](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20II-8250df?style=flat-square) |
| 30–33 | Digital trees (Trie, Patricia), heaps, red-black trees, sets and maps | ![AED II](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20II-8250df?style=flat-square) |
| 34–35 | Secondary memory, B-trees and B*-trees | ![AED II](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20II-8250df?style=flat-square) |
| 36–38 | String processing (brute force, inverted files), exact matching (Shift-And, BM, BMH) and data compression | ![AED II](https://img.shields.io/badge/ALGORITMOS%20E%20ESTRUTURA%20DE%20DADOS%20II-8250df?style=flat-square) |
 
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
 
 
