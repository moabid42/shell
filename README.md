# Overview

The objective of this project is to create a simple shell, like an own little bash.<br>

# About

This shell implementation is a Unix-like command-line interpreter that provides a simple and intuitive interface for interacting with the operating system. It supports various features commonly found in popular shells like Bash, including history of previous entered commands, the ability to search and launch the right executable based on the PATH variable, and environment variable expansion.

The shell also supports wildcards, which can be used to match filenames in the current working directory. The shell also handles common keyboard shortcuts like ctrl-C, ctrl-D, and ctrl-\ in a manner similar to Bash.

The shell implements quoting rules for both single and double quotes, preventing meta-characters from being interpreted within quoted sequences. Environment variables prefixed with $ are expanded to their corresponding values.

### The shell also includes several built-in commands like:
- ```echo``` with option -n
- ```cd``` (relative or absolute path, ```-``` for OLDPWD, without arg for HOME)
- ```pwd``` without options
- ```export``` without options
- ```unset``` without options
- ```env``` without options
- ```exit [exit_status]``` without options

In addition, the shell provides support for input and output redirection, allowing users to redirect input and output to and from files using standard Unix shell syntax. The shell also supports pipes, allowing the output of one command to be passed as input to another command.

This shell implementation is a powerful and flexible tool that provides developers with a lightweight and easy-to-use interface for working with the operating system. Whether you're a seasoned shell user or a beginner, this shell implementation is a great resource for improving your command-line skills.

## Project specifications

For the project we were allowed to use GNU's readline library which handles the terminal interaction (history & input reading).
For everything else the subject allows only to use a few low-level functions and a few POSIX system calls.

<b>Allowed functions:</b>
```readline, rl_clear_history, rl_on_new_line,rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read,close, fork, wait, waitpid, wait3, wait4, signal, sigaction, sigemptyset, sigaddset, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs```

## Dependencies
### Install readline with [brew](https://brew.sh/)
```
brew install readline
```
```
brew link --force readline
```
Add the path to the lib
Replace ~/.zshrc with ~/.bashrc if you use bash instead of zsh
```
echo 'export C_INCLUDE_PATH="/usr/local/opt/readline/include:$C_INCLUDE_PATH"' >> ~/.zshrc
```
```
echo 'export LIBRARY_PATH="/usr/local/opt/readline/lib:$LIBRARY_PATH"' >> ~/.zshrc
```
```
source ~/.zshrc
```
