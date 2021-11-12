# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 10:12:55 by lhoerger          #+#    #+#              #
#    Updated: 2021/11/12 08:27:56 by lhoerger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

FILES = main_bonus.c input_check_bonus.c libft_utils_bonus.c regulate_time_bonus.c killer_bonus.c \
	print_bonus.c daily_work_bonus.c

OBJ = $(FILES:.c=.o)

all: $(NAME)
$(NAME):
	$(CC) $(CFLAGS) -c $(FILES)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
clean:
	rm -f *.o
fclean: clean
	rm -f $(NAME)

re: fclean all

