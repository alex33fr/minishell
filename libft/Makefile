# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: byonis <byonis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 13:49:48 by byonis            #+#    #+#              #
#    Updated: 2026/03/23 09:54:36 by aprivalo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Werror -Wextra

MY_SOURCES = ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_strlen.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_strlcpy.c \
			ft_strlcat.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_strncmp.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strnstr.c \
			ft_atoi.c \
			ft_calloc.c \
			ft_strdup.c \
			ft_substr.c \
			ft_strjoin.c \
			ft_strtrim.c \
			ft_split.c \
			ft_itoa.c \
			ft_strmapi.c \
			ft_striteri.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			strlen_int.c \
			arr_len.c \
			get_next_line_utils.c \
			get_next_line.c \
			ft_printf.c \
			ft_atol.c \
			ft_int_len_un.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

MY_OBJ_BONUS = $(BONUS:.c=.o)

NAME = libft.a

all: $(NAME)

re: fclean all

$(NAME): $(MY_OBJECTS)
	ar rcs $(NAME) $(MY_OBJECTS)

%.o: %.c
	cc $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(MY_OBJECTS)
	rm -f $(MY_OBJ_BONUS)

fclean: clean
	rm -f $(NAME)

.PHONY: all clean fclean re
