# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    config.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rreedy <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/22 09:39:36 by rreedy            #+#    #+#              #
#    Updated: 2020/04/22 21:03:08 by mint             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := ft_ssl

LIBRARY := ft
LIB_DIR := ./libft
LIB_NAME := libft.a
LIB_MAKEFILE := Makefile
LIB_INCLUDE_DIRS := $(LIB_DIR)/includes

SRC_DIRS := ./srcs
SRC_DIRS += ./srcs/md5
SRC_DIRS += ./srcs/sha256
SRC_DIRS += ./srcs/sha224
#SRC_DIRS += ./srcs/sha512

INCLUDE_DIRS := ./includes
INCLUDE_DIRS += ./includes/md5
INCLUDE_DIRS += ./includes/sha256
INCLUDE_DIRS += ./includes/sha224
#INCLUDE_DIRS += ./includes/sha512

CC := gcc
CFLAGS := -g
CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror
CFLAGS += $(foreach include,$(INCLUDE_DIRS),-I$(include)) $(foreach lib_include,$(LIB_INCLUDE_DIRS),-I$(lib_include))
LDFLAGS := -L$(LIB_DIR) -l$(LIBRARY)
