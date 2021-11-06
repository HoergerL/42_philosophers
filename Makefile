NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

FILES = input_check.c main.c ft_atoi.c put_number.c

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

