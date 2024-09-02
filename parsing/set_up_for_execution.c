/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_up_for_execution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 07:09:00 by yait-nas          #+#    #+#             */
/*   Updated: 2024/08/28 00:33:22 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	file_limiter_size(char *tmp)
{
	int	i;

	i = 0;
	while (tmp[i] && tmp[i] != ' ' && tmp[i] != '<' && tmp[i] != '>')
	{
		if (tmp[i] == '"')
		{
			i++;
			while (tmp[i] && tmp[i] != '"')
				i++;
		}
		else if (tmp[i] == '\'')
		{
			i++;
			while (tmp[i] && tmp[i] != '\'')
				i++;
		}
		i++;
	}
	return (i);
}

void	copy_and_blank(char **str, char c, char *dest, int *index)
{
	dest[*index] = **str;
	**str = ' ';
	(*str)++;
	(*index)++;
	while (**str && **str != c)
	{
		dest[*index] = **str;
		**str = ' ';
		(*index)++;
		(*str)++;
	}
}

char	*get_file_limiter(char *tmp)
{
	char	*file_limiter;
	int		i;

	i = 0;
	file_limiter = safe_malloc(file_limiter_size(tmp) + 1);
	while (*tmp && *tmp != ' ' && *tmp != '<' && *tmp != '>')
	{
		if (*tmp == '"' || *tmp == '\'')
			copy_and_blank(&tmp, *tmp, file_limiter, &i);
		file_limiter[i++] = *tmp;
		*tmp = ' ';
		tmp++;
	}
	file_limiter[i] = '\0';
	return (file_limiter);
}

void	fill_up_blank(t_line_splited *empty, int redirection_t, char *tmp)
{
	t_redirection	*redirection;

	if (*tmp == '<' || *tmp == '>')
	{
		*tmp = ' ';
		tmp++;
	}
	while (*tmp == ' ')
		tmp++;
	redirection = safe_malloc(sizeof(t_redirection));
	redirection->redirection_type = redirection_t;
	redirection->file_limiter = get_file_limiter(tmp);
	redirection->next = NULL;
	ft_lstadd_redirection(&(empty->redirection), redirection);
}

void	redirection_input(char *tmp, t_line_splited *empty_node)
{
	*(tmp++) = ' ';
	if (*tmp == '<')
		fill_up_blank(empty_node, 2, tmp);
	else
		fill_up_blank(empty_node, 1, tmp);
}

void	redirection_output(char *tmp, t_line_splited *empty_node)
{
	*(tmp++) = ' ';
	if (*tmp == '>')
		fill_up_blank(empty_node, 4, tmp);
	else
		fill_up_blank(empty_node, 3, tmp);
}

void	ft_extract_redirections_cmd(t_line_splited *empty_node, char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
	{
		if (*tmp == '"' || *tmp == '\'')
			skip_until_find_match(&tmp, *tmp);
		else if (*tmp == '<')
			redirection_input(tmp, empty_node);
		else if (*tmp == '>')
			redirection_output(tmp, empty_node);
		tmp++;
	}
	empty_node->cmd = ft_split_quotes(str, ' ');
	free(str);
}

void	set_up_for_execution(t_line_splited **head, char *line)
{
	int				i;
	char			**line_splited;
	t_line_splited	*tmp;

	line_splited = ft_split_quotes(line, '|');
	i = 0;
	while (line_splited[i])
	{
		tmp = safe_malloc(sizeof(t_line_splited));
		tmp->redirection = NULL;
		tmp->cmd = NULL;
		tmp->next = NULL;
		ft_extract_redirections_cmd(tmp, ft_strdup(line_splited[i]));
		ft_lstadd_line_splited(head, tmp);
		i++;
	}
	free_matrix(line_splited);
}
