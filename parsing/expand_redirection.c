/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:21 by yasser            #+#    #+#             */
/*   Updated: 2024/09/11 11:27:27 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_quotes_redirection(char *str)
{
	char	*new;
	char	*tmp;
	int		i;

	new = safe_malloc(ft_strlen(str) + 1);
	tmp = str;
	i = 0;
	while (*tmp)
	{
		if (*tmp == '"')
		{
			tmp++;
			while (*tmp != '"')
				new[i++] = *(tmp++);
			tmp++;
		}
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	return (new);
}

int	expand_redirection(t_redirection *head, char **env)
{
	char	*tmp;
	char	*old;
	char	**hold;

	while (head)
	{
		if (head->redirection_type != 2)
		{
			old = ft_strdup(head->file_limiter);
			tmp = head->file_limiter;
			tmp = expand_and_leave_quotes(tmp, env);
			hold = ft_split_with_white_spaces(tmp);
			if (how_many_strings(hold) != 1)
			{
				printf("minishell: %s: ambiguous redirect\n", old);
				return (free_matrix(hold), free(old), -1);
			}
			free(tmp);
			head->file_limiter = rm_quotes_redirection(*hold);
			free_matrix(hold);
			free(old);
		}
		head = head->next;
	}
	return (0);
}
