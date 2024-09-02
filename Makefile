NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline
CFLAGS += -fsanitize=address -g3

SRC = \
    built_in_cmd/export/export_0.c \
    built_in_cmd/export/check_functions.c \
    built_in_cmd/export/export_1.c \
    built_in_cmd/export/export_utils.c \
    built_in_cmd/builtin_cmd_1.c \
    built_in_cmd/builtin_cmd_2.c \
    executable_cmd/executable.c \
	execution_utils/execution_utils_0.c \
	execution_utils/execution_utils_1.c \
	execution_utils/execution_utils_2.c \
	link_parsing_execution/manage_cmd.c \
	link_parsing_execution/manage_files_0.c \
	link_parsing_execution/manage_files_1.c \
    link_parsing_execution/get_next_line/get_next_line.c \
    link_parsing_execution/get_next_line/get_next_line_utils.c \
	link_parsing_execution/manage_pipes_0.c	\
	link_parsing_execution/manage_pipes_1.c	\
	handle_errors_and_free/file_1.c			\
	parsing/parsing.c parsing/execution.c parsing/utils.c \
	parsing/clean_up.c parsing/ft_split_quotes.c parsing/set_up_for_execution.c \
	parsing/ft_lstadd_line_splited.c parsing/ft_lstadd_redirection.c \
	parsing/expand.c parsing/ft_strjoin_pro.c parsing/ft_strlcat.c \
	parsing/ft_strlcpy.c\
	main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(READLINE) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME) 

re: fclean all

.PHONY: all fclean re clean bonus
