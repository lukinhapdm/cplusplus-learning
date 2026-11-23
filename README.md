# graduacao-cpp

Códigos, exemplos e exercícios resolvidos em C++ estudados ao longo da graduação, organizados por tema.

## Temas

| Pasta | Tema |
|---|---|
| 01–10 | Fundamentos: introdução, variáveis, operadores, condicionais, funções, repetição, vetores/matrizes, strings, registros, arquivos |
| 11 | TAD, ponteiros e funções |
| 12–14 | Pilha, fila e listas |
| 15–16 | Árvore binária (ABB/AVL) e hash |
| 17 | Algoritmos de ordenação |
| 18–23 | POO: classes, herança, sobrecarga, friend/virtual, polimorfismo, templates e exceções |

Cada pasta tem `exemploXX` (conteúdo da aula) e `exercicioXX` (resolução comentada).

## Como rodar no VS Code

1. Instale um compilador **g++**:
   - **Windows:** [MSYS2](https://www.msys2.org) → no terminal MSYS2 rode `pacman -S mingw-w64-ucrt-x86_64-gcc` e adicione `C:\msys64\ucrt64\bin` ao PATH.
   - **Linux:** `sudo apt install g++ gdb`
   - **macOS:** `xcode-select --install`
2. Confira no terminal: `g++ --version`.
3. Abra a **pasta do repositório** no VS Code e aceite as extensões recomendadas (C/C++ e Code Runner).
4. Abra um `.cpp` e use uma das opções:
   - **Play (Code Runner)** no canto superior direito → compila e executa no terminal.
   - `Ctrl+Shift+P` → *Tasks: Run Task* → **Compilar e executar**.
   - **F5** → depurar (pontos de parada, valores das variáveis).

> **Windows:** se o botão Play der erro com `&&`, o terminal é o PowerShell antigo. Use a task **Compilar e executar** (funciona em qualquer terminal) ou troque o terminal padrão para *Git Bash* / *PowerShell 7*. Acentos na saída já são ajustados pela task.

Pelo terminal: `g++ -std=c++17 arquivo.cpp -o programa && ./programa`
