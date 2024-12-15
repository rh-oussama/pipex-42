/home/oussama Pipex

Pipex is a C programming project that replicates a fundamental UNIX mechanism: pipes. It handles piping between commands, file input/output, and error management. The goal of this project is to deepen your understanding of system-level programming and how processes interact using pipes and file descriptors.

 Project Overview

The program takes four arguments:

```
./pipex file1 cmd1 cmd2 file2
```

Where:
- `file1` and `file2` are file names.
- `cmd1` and `cmd2` are shell commands, with their arguments.

The program should behave like the following shell command:
```
< file1 cmd1 | cmd2 > file2
```

 Example Usage

```bash
$ ./pipex infile "ls -l" "wc -l" outfile
```

This should behave like:

```bash
$ < infile ls -l | wc -l > outfile
```

Another example:

```bash
$ ./pipex infile "grep a1" "wc -w" outfile
```

This should behave like:

```bash
$ < infile grep a1 | wc -w > outfile
```

 Bonus Features

- **Handling Multiple Pipes:**

The basic Pipex program handles piping between two commands using a single pipe (`|`). However, for the bonus part, the program should handle **multiple pipes**, i.e., more than two commands connected in a pipeline.

For example:

```bash
$ ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

This should behave like:

```bash
$ < file1 cmd1 | cmd2 | cmd3 | ... | cmdn > file2
```

**Explanation:**
- This functionality allows you to chain multiple commands together using pipes.
- Each command (`cmd1`, `cmd2`, etc.) should receive input from the previous command in the pipeline and send its output to the next one.
- The output of the last command should be written to `file2`.

**Steps to Implement:**
- You would need to dynamically create pipes for each pair of adjacent commands.
- Fork new processes to run each command, and use `dup2` to redirect standard input and output to the respective pipes.
- Make sure you wait for all child processes to finish and close all file descriptors properly.

- **Support for "here_doc":**

The second bonus feature requires your program to handle the special input redirection `<<` (here-document).

For example:

```bash
$ ./pipex here_doc LIMITER cmd cmd1 file
```

This should behave like:

```bash
$ cmd << LIMITER | cmd1 >> file
```

**Explanation:**
- A **here-doc** is a way to pass input directly to a command in the pipeline without needing an external file.
- Instead of reading from `file1`, the program will use input that is **terminated** by the string `LIMITER`.
- `cmd` will read input up to the point where `LIMITER` is encountered, and this input is passed as input to `cmd`.
- After that, the second command (`cmd1`) will receive the output of `cmd`, and write it to `file`.

**Steps to Implement:**
- If the first argument is `"here_doc"`, you'll need to handle reading input until you encounter `LIMITER`.
- This input will be passed to the first command in the pipeline instead of reading from `file1`.
- The `LIMITER` string should be used to identify the end of the input.
- This will likely involve using `pipe` and `fork`, and writing the collected here-doc data into the pipe.

**Note:** The bonus features will **only** be evaluated if the mandatory part is correctly implemented.

 Requirements

- **Languages**: C
- **Libraries**: Libft (if applicable), standard C libraries
- **Functions**: open, close, read, write, malloc, free, perror, strerror, access, dup, dup2, execve, exit, fork, pipe, unlink, wait, waitpid, and `ft_printf` or its equivalent (which you wrote yourself).

 Compilation

To compile the project, simply run the `Makefile` in the project directory:

```bash
make
```

This will compile the `pipex` program using the flags `-Wall`, `-Wextra`, and `-Werror`.

 Makefile Rules

- **all**: Compiles the program.
- **clean**: Removes object files.
- **fclean**: Removes object files and the compiled program.
- **re**: Recompiles the project.
- **bonus**: (If applicable) Includes any additional functions or features for the bonus part.

 Error Handling

Your program must handle errors gracefully. If any errors occur (such as file not found, invalid arguments, etc.), it should print a descriptive error message and exit cleanly. The program should also avoid memory leaks and handle all heap-allocated memory appropriately.

 Submission

- The project must be submitted in a Git repository.
- The submitted repository should include all source files (`*.c`), headers (`*.h`), and a `Makefile`.
- If you've completed the bonus features, they must be in separate files, and your `Makefile` should include a `bonus` rule.

 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
