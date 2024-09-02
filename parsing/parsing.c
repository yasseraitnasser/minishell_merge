/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 22:10:43 by yait-nas          #+#    #+#             */
/*   Updated: 2024/08/27 10:37:12 by yait-nas         ###   ########.fr       */
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

int	check_what_is_next(char *str)
{
	if (*str)
	{
		while (*str == ' ')
			str++;
		if (*str == '|' || *str == '\0')
			return (-1);
		else
			return (0);
	}
	return (-1);
}

int	with_pipes(char *line)
{
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (*line == '|')
			return (1);
		while (*line && *line != '|')
		{
			if ((*line == '"') | (*line == '\''))
				skip_until_find_match(&line, *line);
			line++;
		}
		if (*line)
		{
			if (check_what_is_next(++line))
				return (1);
		}
		if (*line && *line != '"' && *line != '\'')
			line++;
	}
	return (0);
}

int	redirection_handler(char **str, char c)
{
	(*str)++;
	if (**str == c)
		(*str)++;
	while (**str == ' ')
		(*str)++;
	if (**str == '<' || **str == '|' || **str == '>'
		|| **str == ';' || **str == '\0')
		return (1);
	return (0);
}

int	with_redirections(char *line)
{
	int	flag;

	while (*line)
	{
		flag = 1;
		if (*line == '"' || *line == '\'')
			skip_until_find_match(&line, *line);
		else if (*line == '<' || *line == '>')
		{
			flag = 0;
			if (redirection_handler(&line, *line))
				return (1);
		}
		if (flag)
			line++;
	}
	return (0);
}

int	something_is_wrong(char *line)
{
	if (with_pipes(line))
		return (1);
	if (with_redirections(line))
		return (1);
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
	expand_rm_quotes(head, env);
	return (0);
}
