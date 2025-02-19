# Minishell

## Project overview

The project is a part of the [Hive Helsinki](https://www.hive.fi/en/curriculum) core curriculum. **Minishell** is simple Shell (Unix interface) written in C that uses Bash (Bourne Again SHell) as a reference. The program supports both interactive and non-interactive modes, command history, built-in commands and external executables, and manage POSIX signals. Minishell uses AST (Abstract Syntax Tree to process user input, supporting complex command chains.
This project was developed by [Helena Utzig](https://github.com/hlntzg) and [Natalie Meintjes](https://github.com/Arcane-Jill) as part of the 42 core curriculum.

## Features

#### Interface: 
Provides an interactive command-line prompt using the readline library.
Shows a custom prompt with program name and current working path.
Maintains a command history for easy navigation and reuse.

#### Signal Handling:
The minishell properly responds to key signals:
- `Ctrl-C`: In interactive mode, pressing Ctrl-C displays a new prompt without terminating the shell. In non-interactive mode, it interrupts a running process.
- `Ctrl-D`: In interactive mode, Ctrl-D signals the end of input and exits the shell. In non-interactive mode, it is treated as an End-Of-File (EOF) signal, terminating input.
- `Ctrl-\`: When used in interactive mode, this signal is ignored. However, in non-interactive mode, it forces the termination of the running process.

#### Process user input:
Detects common syntax errors, such as unclosed quotes. 
Handles both single (`'`) and double (`"`) quoted strings.
Tokenizes commands using special characters such as `|`, `<`, `>`, `<<`, `>>`, and strings.
Expands environment variables (`$VAR`).
Supports $? for retrieving the exit status of the last foreground command.

#### Execute command line:
Minishell first processes here-documents before executing commands. It manages file descriptors for input and output redirection, ensuring proper data flow. Command execution follows, with inter-process communication handled through pipes by managing the write-end and read-end.

**Piping and Redirection**

Allows chaining commands by redirecting the output of one process to another using pipes (`|`).
Redirects input (`<`) from a file or implements here-document (`<<`), reading input until a specified delimiter is reached.
Redirects output (`>`) to a file (overwrites existing content) or appends output (`>>`) to a file.
Supports multiple redirections and here-documents, combined or not with pipes, following bash as a reference. 

**Built-in Commands**

Built-in commands are executes directly within the shell, following the convention of returning 0 on success and a non-zero value on failure (accessible via $?). Each built-in receives an array of strings as arguments and the corresponding file descriptor when dealing with redirection to outfile. As a simple command, it is executed in the parent process; when it is part of a pipeline, as a child processing.

**Supported built-ins**

- `echo` – Prints text to the terminal (supports `-n` to omit newline).
- `cd` – Changes the current working directory (supports relative and absolute paths).
- `pwd` – Displays the current working directory.
- `export` – Sets environment variables.
- `unset` – Removes environment variables.
- `env` – Prints the current environment variables.
- `exit` – Exits the shell (support none or only one numeric argument)

**External Commands**

The shell executes external commands by searching for the executable in directories specified by the PATH variable. If no executable was found, a specific error message is displayed and exit status is updated, following bash as a reference. 
Execution process:
1. Creates a new process using `fork()`.
2. Searches for the command in the `PATH`.
3. Executes the command with `execve()`.

## Installation

### What do I need to install Minishell?

To successfully install and run this project, you should have: 

- **Unix-like Operation System**, such as Linux or macOS.
- **C compiler** (e.g. gcc). You can install it using your package manager if not already available.
- **Make Utility**. Make sure `make` is installed to run the `Makefile` provided for compilation.

### How to get and compile the program?

1. **Clone the repository and navigate to the project directory:** First, you need to clone the repository to your local machine and change into the project directory:

```bash
git clone git@github.com:hlntzg/minishell.git && cd minishell/
```

2. **Compile the program:** `Makefile` is included and it automatically handle the compilation for you. After compiling, you will get the executable `minishell`. To compile the program, run:

```bash
make
```

3. **Clean and recompile:** 
- If you want to remove temporary files created during compilation, you can run: `make clean`
- If you want to clean up everything, including the executable and object files, please run: `make fclean`
- If you want to force a full recompilation by cleaning up and then recompiling, you can use: `make re`

## Operating instructions

### How can I execute the program?

Run `./minishell` without arguments.

## Project status

This project was submitted to peer-evaluations and completed. 

## General information

### Lessons learned from the project

- We improved our knowledge of process management, file descriptors, and, of course, shell functionalities.
- We gained experience in constructing and managing abstract syntax trees to effectively parse complex command chains.
- We developed the ability to create and manage child processes, enabling the execution of multiple commands in sequence.

### Permissions and disclaimer

Feel free to use, modify, and share this code. Please provide appropriate attribution when using or modifying it. This project is for educational purposes only. It may contain bugs or incomplete features.

### Copyright and contact information

- Copyright (c) 2024 Helena Utzig, Natalie Meintjes.
- If you have any problems, questions, ideas or suggestions, please reach me out by helenautzig@gmail.com.
- Contact into the 42Network: https://profile.intra.42.fr/users/hutzig.
