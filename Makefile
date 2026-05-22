NAME    = minishell

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

INCLUDES  = -Iincludes -I$(LIBFT_DIR)/includes

OBJ_DIR   = obj

GREEN = \033[0;32m
BLUE  = \033[0;34m
RED   = \033[0;31m
RESET = \033[0m

SRCS =	main.c \
		parsing/expand/expand_utils.c \
		parsing/expand/expand_tools.c \
		parsing/expand/expand_remove_quotes.c \
		parsing/lexer/check_syntax.c \
		parsing/lexer/check_syntax_utils.c \
		parsing/lexer/do_expand.c \
		parsing/lexer/lexer_utils.c \
		parsing/lexer/lexer.c \
		parsing/lexer/search_token.c \
		parsing/lexer/manage_heredoc.c \
		parsing/parsing/parsing_utils.c \
		parsing/parsing/parsing.c \
		parsing/struct_and_free/free.c \
		parsing/struct_and_free/queue.c \
		runtime/builtins/ft_cd.c \
		runtime/builtins/ft_env.c \
		runtime/builtins/ft_simple.c \
		runtime/builtins/ft_tools.c \
		runtime/builtins/ft_tools2.c \
		runtime/builtins/ft_export_sort.c \
		runtime/env/ft_access.c \
		runtime/env/ft_clear.c \
		runtime/env/ft_core.c \
		runtime/env/ft_set.c \
		runtime/env/ft_to_envp.c \
		runtime/env/ft_unset.c \
		runtime/exec/ft_builtin_switch.c \
		runtime/exec/ft_exec.c \
		runtime/exec/ft_childs.c \
		runtime/exec/ft_cmd_list.c \
		runtime/exec/ft_external.c \
		runtime/exec/ft_child_tools.c \
		runtime/exec/ft_heredoc.c \
		runtime/exec/ft_preread_heredoc.c \
		runtime/exec/ft_wait.c \
		runtime/exec/ft_path.c \
		runtime/init/ft_init.c \
		runtime/pipes_redir_signals/ft_pipe.c \
		runtime/pipes_redir_signals/ft_pipe_tools.c \
		runtime/pipes_redir_signals/ft_redir.c \
		runtime/pipes_redir_signals/ft_redir_tools.c \
		runtime/pipes_redir_signals/ft_signals.c \
		runtime/pipes_redir_signals/ft_signal_tools.c \
		runtime/utils/ft_clear.c \
		runtime/utils/ft_close.c \
		runtime/utils/ft_errors.c \
		runtime/utils/ft_errors2.c

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(NAME) $(LIBFT_LIB)

$(LIBFT_LIB):
	@printf "$(BLUE)[Building libft...]$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) >/dev/null 2>&1 || exit 1
	@printf "$(GREEN)[libft OK]$(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(GREEN)[Compiling]$(RESET) $<\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || (printf "$(RED)Error in $<$(RESET)\n"; exit 1)

$(NAME): $(OBJS) $(LIBFT_LIB)
	@printf "$(GREEN)[Linking]$(RESET)\n"
	@$(CC) $(CFLAGS) -no-pie $(OBJS) $(LIBFT_LIB) -lreadline -o $(NAME) || (printf "$(RED)Link error$(RESET)\n"; exit 1)
	@printf "$(GREEN)[100%%] ========[ $(NAME) is ready to work ]======== [OK]$(RESET)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@printf "$(GREEN)Clean [OK]$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@printf "$(GREEN)Fclean [OK]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
