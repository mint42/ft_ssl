# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/16 11:54:37 by rreedy            #+#    #+#              #
#    Updated: 2019/10/16 12:00:11 by rreedy           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ssl
LIB := libft/libft.a

OBJS := $(patsubst %.c,%.o,$(wildcard ./srcs/*.c))

CC := gcc
INCLUDES := -I./includes -I./libft/includes -I./libft/includes/ft_printf
CFLAGS += -g -Wall -Wextra -Werror $(INCLUDES)
LFLAGS += -L./libft -lft

.PHONY: all clean fclean re name

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LFLAGS)

$(LIB):
	@- make -C libft/ all

clean:
	@- $(RM) $(OBJS)
	@- make -C libft/ clean

fclean: clean
	@- $(RM) $(NAME)
	@- make -C libft/ fclean

re: fclean all

#	debug: fclean
#		$(CC) $(CFLAGS) -g $(OBJS) -o $(NAME) $(LFLAGS)
#		@- make -C libft/ debug
