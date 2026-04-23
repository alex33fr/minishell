# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: byonis <byonis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/23 12:43:54 by byonis            #+#    #+#              #
#    Updated: 2026/04/23 13:50:23 by byonis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS := -Wall -Werror -Wextra

INC_DIR := -I includes/

OBJ_DIR := obj

SRC_DIR := srcs/

EXPAND := expand
LEXER := lexer
PARSING := parsing
STRUCT := struct_and_free

LIBFT := libft/libft.a

MY_SOURCES := $(SRC_DIR)$(EXPAND)expand_utils.c \
				$(SRC_DIR)$(EXPAND)expand.c \
				$(SRC_DIR)$(LEXER)check_pipe_quotes.c \
				$(SRC_DIR)$(LEXER)lexer_utils.c \
				$(SRC_DIR)$(LEXER)lexer.c \
				$(SRC_DIR)$(LEXER)search_token.c \
				$(SRC_DIR)$(PARSING)parsing_utils.c \
				$(SRC_DIR)$(PARSING)parsing.c \
				$(SRC_DIR)$(STRUCT)free.c \
				$(SRC_DIR)$(STRUCT)queue.c \
				$(SRC_DIR)main_temp.c

MY_OBJECTS := $(MY_SOURCES:srcs/%.c=$(OBJ_DIR)/%.o)

LIB := $(LIBFT)

NAME := minishell

all : $(LIB) $(NAME) 

$(LIB):
	$(MAKE) -C libft/

$(NAME) : $(MY_OBJECTS)
	cc $(CFLAGS) $(INC_DIR) -o $@ $^ $(LIB) -g

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	cc $(CFLAGS) $(INC_DIR) -o $@ -c $< -g

clean:
	rm -f $(MY_OBJECTS)
	rm -rfd $(OBJ_DIR)
	$(MAKE) -C libft/ clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft/ fclean

re: fclean all

.PHONY: all bonus clean fclean re