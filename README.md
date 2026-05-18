*This project has been created as part of the 42 curriculum by **aprivalo**, **byonis**.*

# minishell

## Description

Minishell is a project designed to create a simple shell. The goal is to develop a functional command-line interpreter inspired by Bash. This project provides extensive knowledge about process management using forks and signals, as well as handling file descriptors, pipes, the global variable, and the environment.
```
Tree of project:
main()
  └── ft_init(envp)                   → t_env* (env linked list)
  └── ft_setup_signals()              → SIGINT=sig_int, SIGQUIT=SIG_IGN
  └── ft_readline_loop()
        └── readline("minishell$ ")
        └── ft_handle_signal()        → if SIGINT → last_status=130
        └── ft_run_line()
              └── ft_env_to_envp()    → t_env* list → char**
              └── lexer()
                    └── check_syntax()
                    └── tokenize_line()
                    └── do_expand()   → $VAR, $?, quote removal
                    └── check_redir()
              └── create_cmds()
                    └── first_cmd() × N
              └── ft_exec_cmd_list()
                    └── n==1 → ft_exec_single()
                          └── dup() save stdin/stdout
                          └── ft_apply_redirs()
                                └── ft_redir_in()       → < file
                                └── ft_redir_out()      → > file
                                └── ft_redir_join()     → >> file
                                └── ft_redir_heredoc()  → << delim
                                      └── ft_heredoc_loop()
                          └── ft_exec_cmd()
                                └── ft_exec_builtin()   → cd, echo, env,
                                │                          export, unset,
                                │                          pwd, exit
                                └── ft_exec_external()
                                      └── fork()
                                      └── ft_resolve_path() → ft_find_path()
                                      └── ft_exec_child()   → execve()
                                      └── ft_wait_child()
                          └── dup2() restore stdin/stdout
                    └── n>1 → ft_exec_pipeline()
                          └── ft_preread_heredocs()
                                └── ft_heredoc_loop() × N
                          └── ft_fork_loop()
                                └── pipe() + fork() × N
                                └── child: ft_child()
                                      └── ft_signals_child()
                                      └── dup2() wire stdin/stdout to pipes
                                      └── ft_apply_redirs()
                                      └── ft_exec_cmd()
                                      └── exit()
                          └── ft_wait_all()
```
## Instructions

### Compilation

The project includes a **Makefile** that compiles the source files with the `-Wall -Wextra -Werror` flags using `cc`. To compile the program, run the following command in your terminal:
```
make
```
This will produce the minishell executable.

### Execution

Run the shell by executing:

```
./minishell
```

## Resources

- [Redirect](https://tuteurs.ens.fr/unix/shell/entreesortie.html)
- [Signals — manpages](http://manpagesfr.free.fr/)
- [Signals — codequoi](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)
- [Built-in — manpages](http://manpagesfr.free.fr/)
- AI: used for explaining concepts, debugging complex problems, and building test cases.