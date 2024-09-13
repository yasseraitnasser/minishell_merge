/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:09 by asabir            #+#    #+#             */
/*   Updated: 2024/09/10 15:44:15 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char **argv)
{
	char			*line;
	t_line_splited	*head;
	t_cmd_track		*c_track;

	c_track = safe_malloc(sizeof(t_cmd_track));
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
			if (!parsing(line, &head, environ))
			{
				execution(head, c_track);
				free_everything(head);
				// display_and_free(head, env);
			}
		}
	}
	else
		write(2, "No arguments required!\n", 23);
}
