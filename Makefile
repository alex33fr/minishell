NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g

LIBFT_DIR   = libft
LIBFT_LIB   = $(LIBFT_DIR)/libft.a

PARSING_DIR = parsing
PARSING_LIB = $(PARSING_DIR)/libparsing.a

RUNTIME_DIR = runtime
RUNTIME_LIB = $(RUNTIME_DIR)/libruntime.a

INCLUDES    = -Iincludes -I$(LIBFT_DIR)/includes

OBJ_DIR     = obj

GREEN = \033[0;32m
BLUE  = \033[0;34m
RED   = \033[0;31m
RESET = \033[0m

all: $(LIBFT_LIB) $(PARSING_LIB) $(RUNTIME_LIB) $(NAME)

$(LIBFT_LIB):
	@printf "$(BLUE)[Building libft...]$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) >/dev/null 2>&1 || exit 1
	@printf "$(GREEN)[libft OK]$(RESET)\n"

$(PARSING_LIB):
	@printf "$(BLUE)[Building parsing...]$(RESET)\n"
	@$(MAKE) -C $(PARSING_DIR) 2>&1 | grep -v "^make" || true
	@printf ""

$(RUNTIME_LIB):
	@printf "$(BLUE)[Building runtime...]$(RESET)\n"
	@$(MAKE) -C $(RUNTIME_DIR) 2>&1 | grep -v "^make" || true
	@printf ""

$(OBJ_DIR)/main.o: main.c
	@mkdir -p $(OBJ_DIR)
	@printf "$(GREEN)[Compiling]$(RESET) main.c\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -c main.c -o $@ || (printf "$(RED)Error in main.c$(RESET)\n"; exit 1)

$(NAME): $(OBJ_DIR)/main.o $(LIBFT_LIB) $(PARSING_LIB) $(RUNTIME_LIB)
	@printf "\r$(GREEN)[Linking]$(RESET)                     "
	@$(CC) $(CFLAGS) $< $(RUNTIME_LIB) $(PARSING_LIB) $(LIBFT_LIB) -lreadline -o $(NAME) || (printf "\n$(RED)Link error$(RESET)\n"; exit 1)
	@printf "\r$(GREEN)[100%%] ========[ $(NAME) is ready to work ]======== [OK] $(RESET)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean >/dev/null 2>&1
	@$(MAKE) -C $(PARSING_DIR) clean >/dev/null 2>&1
	@$(MAKE) -C $(RUNTIME_DIR) clean >/dev/null 2>&1
	@printf "$(GREEN)Clean [OK]$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean >/dev/null 2>&1
	@$(MAKE) -C $(PARSING_DIR) fclean >/dev/null 2>&1
	@$(MAKE) -C $(RUNTIME_DIR) fclean >/dev/null 2>&1
	@printf "$(GREEN)Fclean [OK]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re

