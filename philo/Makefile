NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra -fsanitize=thread -pthread

SRCS = philo.c philo_utils.c philo_rutine.c check_end.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
