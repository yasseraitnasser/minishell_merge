
#include "minishell.h"


int	main(int argc, char **argv, char **env)
{
	char			*line;
	t_line_splited	*head;
    t_cmd_track 	*c_track;

	c_track = malloc(sizeof(t_cmd_track));
    if(c_track == NULL)
    {
		//!handle this
	}
	c_track->exit_value = 0;
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
                execution(head, c_track);
                free_everything(head);
				//display_and_free(head, env);
            }
            
		}
	}
	else
		write(2, "No arguments required!\n", 23);
}
