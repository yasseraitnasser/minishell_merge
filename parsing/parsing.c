/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:10:43 by yait-nas          #+#    #+#             */
/*   Updated: 2024/09/11 10:43:48 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_is_not_closed(char *line)
{
	while (*line)
	{
		if (*line == '"' || *line == '\'')
		{
			skip_until_find_match(&line, *line);
			if (!(*line))
				return (1);
		}
		line++;
	}
	return (0);
}

int	parsing(char *line, t_line_splited **head, char **env)
{
	*head = NULL;
	if (quote_is_not_closed(line))
	{
		printf("syntax error\n");
		return (-1);
	}
	replace_spaces_with_space(line);
	if (something_is_wrong(line))
	{
		printf("syntax error\n");
		return (-1);
	}
	set_up_for_execution(head, line);
	free(line);
	if (expand_and_rm_quotes(head, env))
		return (free_everything(*head), -1);
	return (0);
}
