# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:54:37 by rreedy            #+#    #+#              #
#    Updated: 2019/10/17 14:57:22 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ssl
LIB := libft/libft.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))
MD5_OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/md5/*.c))
SHA256_OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/sha256/*.c))

CC := gcc
INCLUDES := -I./includes -I./libft/includes -I./libft/includes/ft_printf
CFLAGS += -g -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./libft -lft

.PHONY: all clean fclean re name

all: $(NAME)

$(NAME): $(LIB) $(OBJS) $(MD5_OBJS) $(SHA256_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MD5_OBJS) $(SHA256_OBJS) -o $(NAME) $(LFLAGS)

$(LIB):
	@- make -C libft/ all

clean:
	@- $(RM) $(OBJS) $(MD5_OBJS) $(SHA256_OBJS)
	@- make -C libft/ clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft/ fclean

re: fclean all
