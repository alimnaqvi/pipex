# Pipex
[![C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Makefile](https://img.shields.io/badge/Build-Makefile-brightgreen.svg)](https://www.gnu.org/software/make/)

This is a 42 school project to learn about shell pipes by implementing them in C. The goal is to replicate the behavior of shell pipelines (`|`) and redirections (`<`, `>`), which are fundamental concepts in Unix-based systems.

### Task Description

The program takes four arguments:
1. `file1`: The input file.
2. `cmd1`: The first command to execute.
3. `cmd2`: The second command to execute.
4. `file2`: The output file.

The program behaves exactly the same as running the following shell command:
```
< file1 cmd1 | cmd2 > file2
```

The implementation involves:
- Opening `file1` for reading and `file2` for writing.
- Creating a pipe to connect the output of `cmd1` to the input of `cmd2`.
- Using `fork()` to create child processes for executing `cmd1` and `cmd2`.
- Managing file descriptors to redirect input/output as required.
- Handling edge cases such as missing files, invalid commands, or permission errors.

### Usage

To compile and run the program:
```
make
./pipex file1 cmd1 cmd2 file2
```

Examples:
- `./pipex infile "ls -l" "wc -l" outfile` behaves like `< infile ls -l | wc -l > outfile`.
- `./pipex infile "grep a1" "wc -w" outfile` behaves like `< infile grep a1 | wc -w > outfile`.

### Concepts Learned and Applied

<p>
  This project was a great learning experience and helped me deepen my understanding of the following concepts:
  <img src="https://page-views-counter-534232554413.europe-west1.run.app/view?src=github.com&src_uri=/alimnaqvi/pipex" style="display: none;" />
</p>

- **Process Management**:
  - Using `fork()` to create child processes.
  - Understanding how parent and child processes interact.
  - Using `waitpid()` to manage process termination and retrieve exit statuses.

- **Pipes and File Redirection**:
  - Creating and managing pipes with `pipe()`.
  - Redirecting input/output using `dup2()` to mimic shell behavior.
  - Handling file descriptors carefully to avoid leaks or unintended behavior.

- **File Handling in C**:
  - Opening files with `open()` and managing permissions.
  - Handling errors when files are missing or permissions are insufficient.
  - Using `/dev/null` as a fallback for invalid input files.

- **Command Execution**:
  - Using `execve()` to execute commands in child processes.
  - Parsing and preparing commands, including handling quoted arguments.
  - Searching for executables in the `PATH` environment variable.

- **Memory Management**:
  - Allocating and freeing resources dynamically to prevent memory leaks.
  - Implementing helper functions to clean up resources on errors or program termination.

- **Error Handling**:
  - Providing meaningful error messages using `perror()` and custom messages.
  - Handling edge cases such as invalid arguments, missing files, or inaccessible commands.

- **String Manipulation**:
  - Implementing a custom `ft_split_with_quotes()` function to handle arguments with quotes.
  - Trimming quotes from parsed arguments for proper command execution.

This project was a stepping stone for more advanced projects, especially [minishell](https://github.com/alimnaqvi/minishell), where I further explored shell behavior and implemented a custom shell from scratch.
