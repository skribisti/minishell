NAME = minishell

CFLAGS = -Wall -Wextra -Werror
SRCS = parsing.c ft_split.c
OBJS = $(SRCS:.c=.o)
LIBS = -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	cc $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

dev: fclean
	git add *; git commit -m "dev"; git push;

.PHONY: all clean fclean re dev