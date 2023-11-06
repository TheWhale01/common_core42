CC=c++
CFLAGS=-Wall -Wextra -Werror -std=c++98
CFILES=tests.cpp Account.cpp
OBJS=$(patsubst %.cpp, %.o, $(CFILES))
NAME=account

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re