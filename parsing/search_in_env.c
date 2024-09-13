/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_in_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:31 by yasser            #+#    #+#             */
/*   Updated: 2024/09/10 09:21:33 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_key(char **str)
{
	char	*key;
	int		j;

	if (is_digit(**str))
	{
		key = ft_strndup(*str, 1);
		(*str)++;
		return (key);
	}
	if (**str == '?')
		return (ft_strdup("?"));
	key = *str;
	j = 0;
	while (is_alphanumeric(key[j]))
		j++;
	key = safe_malloc(j + 1);
	j = 0;
	while (is_alphanumeric(**str))
	{
		key[j++] = **str;
		(*str)++;
	}
	key[j] = '\0';
	return (key);
}

char	*norminette(char **str)
{
	(*str)++;
	return (ft_strdup("$?"));
}

char	*get_value(char *key, char **env, char **str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	if (*key == '?')
		return (norminette(str));
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
