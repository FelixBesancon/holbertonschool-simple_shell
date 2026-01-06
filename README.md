---
# Holberton School - Simple Shell
### `./hsh` - A custom UNIX command line interpreter

---
## 1. Description

### This project is a simple implementation of a UNIX command line interpreter written in C language for Holberton School France curriculum.  

The goal is to understand how a shell works internally by recreating its core behavior using system calls such as `fork`, `execve`, and `wait`.
The shell reads commands from standard input, executes them, and displays the result, mimicking the behavior of `/bin/sh` for basic use cases.

---
## 2. Requirements
- Allowed editors: `vi`, `vim`, `emacs`
- Compiled on **Ubuntu 20.04 LTS**
- All files end with a new line
- No memory leaks
- Maximum of 5 functions per file
- All header files are include-guarded
- Only allowed system calls and functions are used
- The code follows the Betty coding style
- Project written in C following the Holberton School style guidelines

---
## 3. Allowed functions and system calls

- All functions from `<string.h>`
- `fork`, `execve`, `wait`, `waitpid`
- `malloc`, `free`
- `getline`
- `stat`, `access`
- `perror`, `printf`
- `exit`, `_exit`
- `read`, `write`
- `getpid`, `isatty`
- `signal`, `kill`
- And other functions explicitly listed in the project requirements

---
## 4. Compilation

- Compilation flags as required are:
  ```sh
  gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
  ```

---
## 5. Usage

---
## 6. How it works

---
## 7. Flowchart

---
## 8. Limitations & Future Improvements

---
## 9. Testing & Error Handling

---
## 10. Man Page

- A man page is available with the project:
```bash
man ./shell
```

---
## 11. Authors

- **Alexis LAUBERT**
  GitHub: https://github.com/loties1533
- **Felix BESANCON**
  Github: https://github.com/FelixBesancon

---
## 12. Date

December 2025

---
