# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhoerger <lhoerger@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/11 10:12:55 by lhoerger          #+#    #+#              #
#    Updated: 2021/11/11 10:12:56 by lhoerger         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra 
RM = rm -f

FILES = input_check.c main.c libft_utils.c put_number.c prints.c create_threads.c eat.c daily_work.c regulate_time.c free.c daily_work_utils.c

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

