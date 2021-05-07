# Minishell_
The objective of this project is for you to create a simple shell. Yes, your own little bash or zsh. You will learn a lot about processes and file descriptors.
## Contributors:
  <ul>
    <li><b>Mojahid BELAMAN</b> &nbsp;&nbsp;=> <a href="https://www.linkedin.com/in/mojahid-belaman/" target="_blank">LinkedIn</a></li>
    <li><b>Khaoula NABOUSSI</b
    > => <a href="https://www.linkedin.com/in/khaoula-naboussi-621646199/" target="_blank">LinkedIN</a></li>
  </ul>

## Subject:
* Not use more than one global variable, think about it and be ready to explain why you do it.
* Show a prompt when waiting for a new command.
* Search and launch the right executable (based on the ``PATH`` variable or by using
  relative or absolute path) like in bash.
* It must implement the builtins like in bash:

      - echo with option ’-n’
      
      - cd with only a relative or absolute path
      
      - pwd without any options
      
      - export without any options
      
      - unset without any options
      
      - env without any options and any arguments
      
      - exit without any options
      
* ``;`` in the command should separate commands like in bash
* ``’`` and ``"`` should work like in bash except for multiline commands
* Redirections ``<`` ``>`` ``“>>”`` should work like in bash except for file descriptor aggregation
* Pipes ``|`` should work like in bash except for multiline commands
* Environment variables (``$`` followed by characters) should work like in bash
* ``$?`` should work like in bash
* ``ctrl-C``, ``ctrl-D`` and ``ctrl-\`` should have the same result as in bash
* Use up and down arrows to navigate through the command using termcap (mandatory) history which we will then be able to edit (at least like we can for classic lines)
if we feel like it (the line, not the history).

## External functions:
```
printf, malloc, free, write, open, read, close, fork, wait, waitpid, wait3, wait4, signal, kill,
exit, getcwd, chdir, stat, lstat, fstat, execve, dup, dup2, pipe, opendir, readdir, closedir,
strerror, errno, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```

## How to use?
1.  `make`  
2.  `./minishell`
3.  Run commands
