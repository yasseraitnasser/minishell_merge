/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:20:47 by yasser            #+#    #+#             */
/*   Updated: 2024/09/10 09:20:49 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	single_quotes_handler(char **str, char *new, int *i)
{
	new[*i] = **str;
	(*i)++;
	(*str)++;
	while (**str && **str != '\'')
	{
		new[*i] = **str;
		(*i)++;
		(*str)++;
	}
	new[*i] = **str;
	(*i)++;
	(*str)++;
}

void	found_dolar_sign(char **str, char **new, int *i, char **env)
{
	char	*key;
	char	*value;

	(*str)++;
	key = get_key(str);
	value = get_value(key, env, str);
	free(key);
	*new = ft_strjoin_pro(*new, value, *str);
	*i = ft_strlen(*new);
}

void	double_quotes_handler(char **str, char **new, int *i, char **env)
{
	new[0][*i] = **str;
	(*i)++;
	(*str)++;
	while (**str && **str != '"')
	{
		if (**str == '$')
		{
			new[0][*i] = '\0';
			found_dolar_sign(str, new, i, env);
		}
		else
		{
			new[0][*i] = **str;
			(*i)++;
			(*str)++;
		}
	}
	new[0][*i] = **str;
	(*i)++;
	(*str)++;
}

char	*expand_and_leave_quotes(char *str, char **env)
{
	char	*new;
	int		i;
	char	*tmp;

	new = safe_malloc(ft_strlen(str) + 1);
	i = 0;
	tmp = str;
	while (*str)
	{
		if (*str == '\'')
			single_quotes_handler(&str, new, &i);
		else if (*str == '"')
			double_quotes_handler(&str, &new, &i, env);
		else if (*str == '$')
		{
			new[i] = '\0';
			found_dolar_sign(&str, &new, &i, env);
		}
		else
			new[i++] = *(str++);
	}
	new[i] = '\0';
	return (free(tmp), new);
}

void	expand_cmd(char **cmd, char **env)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		cmd[i] = expand_and_leave_quotes(cmd[i], env);
		i++;
	}
}
