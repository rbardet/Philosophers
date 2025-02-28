# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 22:28:21 by rbardet-          #+#    #+#              #
#    Updated: 2025/02/28 22:33:09 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = src/philo.c \
	src/philo_utils.c \
	src/init.c

INCLUDE = -I SOURCES

OBJ_DIR = obj
OBJECTS = $(SOURCES:src/%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

