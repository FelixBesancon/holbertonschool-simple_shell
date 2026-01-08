---
# Holberton School - Simple Shell
### `./hsh` - A custom UNIX command line interpreter

---
## 1. Description

- This project is a simple implementation of a UNIX command line interpreter written in C language for Holberton School France curriculum.  

The goal is to understand how a shell works internally by recreating its core behavior using system calls such as `fork`, `execve`, and `wait`.
The shell reads commands from standard input, executes them, and displays the result, mimicking the behavior of `/bin/sh` for basic use cases.

---
## 2. Requirements
- Allowed editors: `vi`, `vim`, `emacs`
- Compiled on **Ubuntu 20.04 LTS**
- All files end with a new line
- No memory leaks (valgrind clean)
- Maximum of 5 functions per file
- All header files are include-guarded
- Only allowed system calls and functions are used
- The code follows the Betty coding style
- Project written in C following the Holberton School style guidelines

---
## 3. Allowed functions and system calls

- All functions from `<string.h>` as allowed by the project requirements
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

- Examples of correct use:
  ```sh
  Interactive mode:
  $ ./hsh
  ($) ls -l
  ($) env
  ($) exit
  ```
  ```sh
  Non interactive mode:
  $ echo "ls" | ./hsh
  $ cat commands.txt | ./hsh
  ```

---
## 6. How it works

The shell follows a simple execution loop that mimics the basic behavior of a UNIX shell.

1. The program initializes its main variables, including the input buffer, the exit status of the last executed command, and a line counter.
2. An infinite loop starts and displays a prompt if the standard input is a terminal (interactive mode).
3. The shell reads a line from standard input using `getline`.
   - If an end-of-file (EOF) is reached, the shell exits the loop.
   - If the input line is empty, the shell returns to the beginning of the loop.
4. The input line is split into tokens (command and arguments).
5. The shell checks whether the command is a built-in:
   - `exit`: frees allocated memory and terminates the shell using the last exit status.
   - `env`: prints the current environment variables.
6. If the command is not a built-in, the shell attempts to resolve the command path:
   - If the command contains a `/`, it is treated as an absolute or relative path.
   - Otherwise, the shell searches for the command in the directories listed in the `PATH` environment variable.
7. If the command is found and executable, the shell creates a child process using `fork`.
   - The child process executes the command using `execve`.
   - If execution fails, an error message is printed and the child exits with status `127`.
8. The parent process waits for the child to terminate, retrieves its exit status, and updates the internal status accordingly.
9. The shell increments the command counter and returns to the beginning of the loop.

---
## 7. Flowchart

![Simple Shell Flowchart](holberton-simple_shell.flowchart.svg)

---
## 8. Limitations & Future Improvements

### Current limitations

- The shell does not support pipes (`|`) or input/output redirections (`>`, `<`, `>>`).
- Quoted strings and argument escaping are not handled.
- Command chaining operators such as `;`, `&&`, and `||` are not supported.
- Environment variable expansion (e.g. `$HOME`) is not implemented.
- Only a limited set of built-in commands is available (`exit` and `env`).
- Signal handling is minimal and does not fully replicate the behavior of standard shells.

### Possible future improvements

- Implement support for pipes and redirections.
- Add parsing for quoted strings and escaped characters.
- Extend built-in commands (`cd`, `setenv`, `unsetenv`, etc.).
- Improve signal handling (Ctrl+C, Ctrl+D, Ctrl+Z).
- Implement environment variable expansion.

---
## 9. Testing & Error Handling

The shell has been tested in both interactive and non-interactive modes.

### Interactive mode testing

```sh
$ ./hsh
($) ls
($) env
($) unknown_command
($) exit
```

### Non-interactive mode testing

```sh
$ echo "ls -l" | ./hsh
$ echo "env" | ./hsh
$ echo "unknown_command" | ./hsh
```

### Error handling

- If a command cannot be found, the shell prints an error message and returns exit status 127.
- If fork fails, an error message is displayed and the shell continues execution.
- If execve fails in the child process, an error message is printed and the child exits with status 127.
- The shell correctly propagates the exit status of executed commands.

### Memory management

- All dynamically allocated memory is properly freed.
- The program has been tested with valgrind to ensure no memory leaks occur.

```sh
valgrind --leak-check=full ./hsh
```

---
## 10. Man Page

- A man page is available with the project:
```bash
man ./man_1_simple_shell
```

---
## 11. Authors

- **Alexis LAUBERT** — GitHub: `https://github.com/loties1533`
- **Felix BESANCON** — Github: `https://github.com/FelixBesancon`

---
## 12. Date

Holberton School France - January 2026

---
