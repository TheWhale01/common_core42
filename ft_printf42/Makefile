CC=gcc
CFLAGS=-Wall -Wextra -Werror
CFILES=ft_printf.c ft_putstr.c ft_strlen.c ft_putnbr.c
OBJS=${CFILES:.c=.o}
NAME=libftprintf.a

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 