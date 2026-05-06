CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

INC_DIR = -I ../includes/ -I ../libft/includes/

OBJ_DIR = obj

BUILTINS = builtins/
ENV      = env/
EXEC     = exec/
INIT     = init/
PIPES    = pipes_redir_signals/
UTILS    = utils/

NAME     = libruntime.a

GREEN    = \033[0;32m
RED      = \033[0;31m
RESET    = \033[0m

MY_SOURCES = $(BUILTINS)ft_builtin_env.c \
             $(BUILTINS)ft_builtin_simple.c \
             $(ENV)ft_env_access.c \
             $(ENV)ft_env_clear.c \
             $(ENV)ft_env_core.c \
             $(ENV)ft_env_set.c \
             $(ENV)ft_env_to_envp.c \
             $(ENV)ft_env_unset.c \
             $(EXEC)ft_exec_builtin.c \
             $(EXEC)ft_exec.c \
             $(EXEC)ft_exec_childs.c \
             $(EXEC)ft_exec_cmd_list.c \
             $(EXEC)ft_exec_external.c \
             $(EXEC)ft_exec_wait.c \
             $(EXEC)ft_path.c \
             $(INIT)ft_init.c \
             $(PIPES)ft_pipe.c \
             $(PIPES)ft_redir.c \
             $(PIPES)ft_signals.c \
             $(UTILS)ft_clear.c \
             $(UTILS)ft_close.c \
             $(UTILS)ft_errors.c \
             $(UTILS)ft_redir_tools.c \
             $(UTILS)ft_builtins_tools.c \
             $(UTILS)ft_pipe_tools.c

MY_OBJECTS     = $(addprefix $(OBJ_DIR)/, $(MY_SOURCES:.c=.o))
TOTAL_FILES   := $(words $(MY_SOURCES))
COUNT          = 0

all: $(NAME)

$(NAME): $(MY_OBJECTS)
	@printf "\r$(GREEN)[Archiving]$(RESET)                   "
	@ar rcs $@ $^
	@printf "\r$(GREEN)[100%%] ========[ $(NAME) is ready ]======== [OK] $(RESET)\n"

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PERCENT=$$(($(COUNT)*100/$(TOTAL_FILES))); \
	printf "\r$(GREEN)[%3d%%] %-30s$(RESET)" $$PERCENT "$<"; \
	$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@ || (printf "\n$(RED)Error in $<$(RESET)\n"; exit 1)

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(GREEN)Clean [OK]$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(GREEN)Fclean [OK]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
