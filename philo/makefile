# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbardet- <rbardet-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 22:28:21 by rbardet-          #+#    #+#              #
#    Updated: 2025/03/08 14:17:55 by rbardet-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = src/main.c \
	src/philo_utils.c \
	src/init.c \
	src/routine.c \
	src/routine_state.c

INCLUDE = -I includes

OBJ_DIR = obj
OBJECTS = $(SOURCES:%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDE)

all: $(NAME)

$(NAME): $(OBJECTS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)

$(OBJ_DIR)/src/%.o: src/%.c | $(OBJ_DIR)/src
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/src :
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
