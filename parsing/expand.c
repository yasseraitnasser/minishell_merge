/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 16:20:00 by yait-nas          #+#    #+#             */
/*   Updated: 2024/09/02 19:52:41 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_alphanumeric(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

void	single_quotes_handler(char **tmp, char *new, int *i)
{
	(*tmp)++;
	while (**tmp && **tmp != '\'')
	{
		new[*i] = **tmp;
		(*i)++;
		(*tmp)++;
	}
	(*tmp)++;
}

char	*search_for_value(char *key, char **env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
		{
			if (env[i][j] != key[j])
				break ;
			j++;
		}
		if (env[i][j] == '=' && !key[j])
		{
			value = ft_strdup(env[i] + j + 1);
			return (value);
		}
		i++;
	}
	return (ft_strdup(""));
}

void	found_ds_inside_dq(char **tmp, char **new, int *i, char **env)
{
	int		j;
	char	*key;
	char	*value;

	(*tmp)++;
	j = 0;
	key = *tmp;
	while (is_alphanumeric(key[j]))
		j++;
	key = safe_malloc(j + 1);
	j = 0;
	while (is_alphanumeric(**tmp))
	{
		key[j++] = **tmp;
		(*tmp)++;
	}
	key[j] = '\0';
	value = search_for_value(key, env);
	free(key);
	*new = ft_strjoin_pro(*new, value, *tmp);
	*i = ft_strlen(*new);
}

void	double_quotes_handler(char **tmp, char **new, int *i, char **env)
{
	(*tmp)++;
	while (**tmp && **tmp != '"')
	{
		if (**tmp == '$')
		{
			new[0][*i] = '\0';
			found_ds_inside_dq(tmp, new, i, env);
		}
		else
		{
			new[0][*i] = **tmp;
			(*i)++;
			(*tmp)++;
		}
	}
	(*tmp)++;
}

// void	none_of_them_handler(char **cmd, int index)
// {
	
// }

void	clean_cmd(char **cmd, int index, char **env)
{
	char	*new;
	char	*tmp;
	int		i;

	new = safe_malloc(ft_strlen(cmd[index]) + 1);
	i = 0;
	tmp = cmd[index];
	while (*tmp)
	{
		if (*tmp == '\'')
			single_quotes_handler(&tmp, new, &i);
		else if (*tmp == '"')
			double_quotes_handler(&tmp, &new, &i, env);
		// else if (*tmp == '$')
		// 	none_of_them_handler(cmd, index, new);
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	free(cmd[index]);
	cmd[index] = new;
}

void	expand_cmd(char **cmd, char **env)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		clean_cmd(cmd, i, env);
		i++;
	}
}

void	expand_rm_quotes(t_line_splited **head, char **env)
{
	t_line_splited	*tmp;

	tmp = *head;
	while (tmp)
	{
		expand_cmd(tmp->cmd, env);
		//expand_redirection(tmp->redirection, env);
		tmp = tmp->next;
	}
}
