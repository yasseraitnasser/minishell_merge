NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address
READLINE = -lreadline
FILES = main.c parsing.c execution.c utils.c \
	clean_up.c ft_split_quotes.c set_up_for_execution.c \
	ft_lstadd_line_splited.c ft_strdup.c ft_lstadd_redirection.c \
	ft_strlen.c expand.c ft_strjoin_pro.c ft_strlcat.c \
	ft_strlcpy.c

FILES_o = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(FILES_o)
	$(CC) $(CFLAGS) $(FILES_o) $(READLINE) -o $(NAME)

clean:
	rm -f $(FILES_o)

fclean: clean
	rm -f $(NAME)

re: fclean all
