CC      = cc
CFLAGS  = -Wall -Wextra -Werror -g

INC_DIR = -I ../includes/ -I ../libft/includes/

OBJ_DIR = obj

EXPAND  = expand/
LEXER   = lexer/
PARSING = parsing/
STRUCT  = struct_and_free/

NAME    = libparsing.a

GREEN   = \033[0;32m
RED     = \033[0;31m
RESET   = \033[0m

MY_SOURCES = $(EXPAND)expand_utils.c \
             $(EXPAND)expand.c \
             $(LEXER)check_syntax.c \
             $(LEXER)lexer_utils.c \
             $(LEXER)lexer.c \
             $(LEXER)search_token.c \
             $(PARSING)parsing_utils.c \
             $(PARSING)parsing.c \
             $(STRUCT)free.c \
             $(STRUCT)queue.c

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

re:	fclean all

.PHONY: all clean fclean re