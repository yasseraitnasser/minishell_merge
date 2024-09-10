/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <yait-nas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:45:30 by yait-nas          #+#    #+#             */
/*   Updated: 2023/11/28 12:41:34 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_words_exam(char const *s)
{
	int		count;

	count = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s)
			count++;
		while (*s && !is_space(*s))
			s++;
	}
	return (count);
}

static int	c_char(char const *s)
{
	int	i;

	i = 0;
	while (s[i] && !is_space(s[i]))
		i++;
	return (i);
}

static char	*word(char const *s, char **strings, int index)
{
	int		i;
	char	*p;

	i = 0;
	p = malloc(sizeof(char) * (c_char(s) + 1));
	if (!p)
	{
		if (index)
		{
			while (index--)
				free(strings[index]);
		}
		free(strings);
		return (NULL);
	}
	while (!is_space(s[i]) && s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split_exam(char const *s)
{
	char	**strings;
	int		string_index;

	if (!s)
		return (NULL);
	strings = malloc(sizeof(char *) * (count_words_exam(s) + 1));
	if (!strings)
		return (NULL);
	string_index = 0;
	while (*s)
	{
		while (is_space(*s))
			s++;
		if (*s)
		{
			strings[string_index] = word(s, strings, string_index);
			if (!strings[string_index])
				return (NULL);
			string_index++;
		}
		while (*s && !is_space(*s))
			s++;
	}
	strings[string_index] = NULL;
	return (strings);
}
