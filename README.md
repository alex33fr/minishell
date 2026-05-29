*This project has been created as part of the 42 curriculum by **aprivalo**, **byonis**.*

# minishell

## Description

Minishell is a project designed to create a simple shell. The goal is to develop a functional command-line interpreter inspired by Bash. This project provides extensive knowledge about process management using forks and signals, as well as handling file descriptors, pipes, the global variable, and the environment.

## Features

- Interactive prompt with command history (readline)
- Pipes (`|`) between commands
- Redirections : `<` `>` `>>` `<<` (heredoc)
- Variable expansion (`$VAR`, `$?`)
- Single and double quote handling
- Signals : `Ctrl+C`, `Ctrl+D`, `Ctrl+\`
- Built-in commands : `cd`, `echo`, `env`, `export`, `unset`, `pwd`, `exit`

## Project structure

```
minishell/
├── main.c                  → entry point, readline loop, ft_init
├── includes/
│   ├── minishell.h
│   ├── parsing.h
│   ├── runtime.h
│   └── globals.h
├── parsing/
│   ├── lexer/          → tokenize, syntax check, expand, heredoc
│   ├── expand/         → variable expansion, quote removal
│   ├── parsing/        → build t_cmd list
│   └── struct_and_free/
├── runtime/
│   ├── builtins/           → ft_cd, ft_env, ft_simple (pwd/exit), ft_tools,
│   │                          ft_tools2 (echo/export), ft_export_sort
│   ├── env/                → env linked list: ft_core, ft_access, ft_set,
│   │                          ft_unset, ft_clear, ft_to_envp
│   ├── exec/               → ft_exec, ft_cmd_list, ft_builtin_switch, ft_external,
│   │                          ft_childs, ft_child_tools, ft_wait, ft_heredoc, ft_path
│   ├── pipes_redir_signals/ → ft_pipe, ft_pipe_tools, ft_redir, ft_redir_tools,
│   │                          ft_signals, ft_signal_tools
│   └── utils/              → ft_clear, ft_close, ft_errors, ft_errors2
└── libft/
```

## Call tree

```
main()
  ├── ft_init(envp)                   → t_env* (env linked list)
  │     └── ft_setup_signals()        → SIGINT=sig_int, SIGQUIT=SIG_IGN
  └── ft_readline_loop()
        ├── readline("🔥66🔥$ ")          ← interactive
        ├── ft_readline_nointeractive()            ← no-interactive
        │     └── ft_read_heredoc_line() [×2 if line ends with |]
        ├── ft_handle_signal()        → if SIGINT → last_status=130
        └── ft_run_line()
              ├── ft_env_to_envp()    → t_env* list → char**
              ├── lexer()
              │     ├── check_syntax()
              │     ├── tokenize_line()
              │     ├── do_expand()      → $VAR, $?, quote removal
              │     └── check_redir()
              ├── create_cmds()
              │     └── first_cmd() × N
              └── ft_exec_cmd_list()
                    ├── n==1 → ft_exec_single()
                    │     ├── (no redir) ft_exec_cmd()
                    │     └── (redir) dup() + ft_exec_redir()
                    │           ├── ft_preread_heredocs()  → << delim (pre-read)
                    │           ├── ft_apply_redirs()
                    │           │     ├── ft_redir_in()       → < file
                    │           │     ├── ft_redir_out()      → > file
                    │           │     ├── ft_redir_join()     → >> file
                    │           │     └── ft_redir_heredoc()  → << delim
                    │           │           └── ft_heredoc_loop()
                    │           ├── ft_exec_cmd()
                    │           │     ├── ft_exec_builtin()   → cd, echo, env,
                    │           │     │                          export, unset,
                    │           │     │                          pwd, exit
                    │           │     └── ft_exec_external()
                    │           │           ├── fork()
                    │           │           ├── ft_resolve_path() → ft_find_path()
                    │           │           ├── ft_exec_child()   → execve()
                    │           │           └── ft_wait_child()
                    │           └── ft_restore_fds()
                    └── n>1 → ft_exec_pipeline()
                          ├── ft_preread_heredocs()
                          │     └── ft_heredoc_loop() × N
                          ├── ft_fork_loop()
                          │     ├── pipe() + fork() × N
                          │     └── child: ft_child()
                          │           ├── ft_signals_child()
                          │           ├── dup2() wire stdin/stdout to pipes
                          │           ├── ft_apply_redirs()
                          │           ├── ft_exec_cmd()
                          │           └── exit()
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

- [Redirections — GNU Bash manual](https://www.gnu.org/software/bash/manual/bash.html#Redirections)
- [Signals — man7.org](https://man7.org/linux/man-pages/man7/signal.7.html)
- [Built-ins — GNU Bash manual](https://www.gnu.org/software/bash/manual/bash.html#Shell-Builtin-Commands)
- AI: used for explaining concepts, debugging complex problems, and building test cases.
