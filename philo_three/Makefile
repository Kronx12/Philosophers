CC=gcc
CFLAGS=-Wall -Wextra -Werror -g3 -fsanitize=address
RM=rm -rf
NAME=philo_three

INC=./includes/global.h
SRCS=	./srcs/main.c \
		./srcs/errors.c \
		./srcs/utils.c \
		./srcs/timer.c \
		./srcs/philo.c \
		./srcs/logger.c
OBJS=$(SRCS:.c=.o)
LIB=-lpthread

%.c%.o:
	$(CC) $(CFLAGS) -c $< -o $@

all:		$(NAME)

$(OBJS):	$(INC)

$(NAME):	$(INC) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIB) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:	all clean fclean re