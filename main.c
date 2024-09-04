
#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_line_splited	*head;

	(void)argv;
	if (argc == 1)
	{
		while (1)
		{
			line = readline("\033[0;33mMINISHELL : \033[0m");
			if (!line)
			{
				printf("exit\n");
				break ;
			}
			add_history(line);
			if (!parsing(line, &head, env))
            {
                execution(head);
                free_everything(head);
				// display_and_free(head, env);
            }

		}
	}
	else
		write(2, "No arguments required!\n", 23);
}
