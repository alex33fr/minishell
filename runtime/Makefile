NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = ../libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

INCLUDES    = -Iincludes -I$(LIBFT_DIR)/includes

OBJ_DIR     = obj
SRCS        = main.c \
              env/ft_env_access.c \
			  env/ft_env_clear.c \
              env/ft_env_core.c \
              env/ft_env_set.c \
			  env/ft_env_unset.c \
			  env/ft_env_to_envp.c \
              utils/ft_clear.c \
			  utils/ft_strcmp.c \
			  utils/ft_close.c \
			  exec/ft_exec_childs.c \
			  exec/ft_exec_external.c \
			  exec/ft_exec_builtin.c \
			  exec/ft_exec_wait.c \
			  exec/ft_exec.c \
			  exec/ft_path.c
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

TOTAL_FILES := $(words $(SRCS))
COUNT = 0

GREEN = \033[0;32m
BLUE  = \033[0;34m
RED   = \033[0;31m
RESET = \033[0m

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@printf "\r$(GREEN)[Linking]$(RESET)                     "
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) || (printf "\n$(RED)Link error$(RESET)\n"; exit 1)
	@printf "\r$(GREEN)[100%%] $(NAME) ready [OK]$(RESET)\n"

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR) >/dev/null 2>&1 || exit 1

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@PERCENT=$$(($(COUNT)*100/$(TOTAL_FILES))); \
	printf "\r$(GREEN)[%3d%%] %-30s$(RESET)" $$PERCENT "$<"; \
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ || exit 1

clean:
	@rm -rf $(OBJ_DIR)
	@if [ -d "$(LIBFT_DIR)" ]; then $(MAKE) -C $(LIBFT_DIR) clean >/dev/null 2>&1; fi
	@printf "$(GREEN)Clean [OK]$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@printf "$(GREEN)Fclean [OK]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
