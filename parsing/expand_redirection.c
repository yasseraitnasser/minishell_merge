/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 09:21:21 by yasser            #+#    #+#             */
/*   Updated: 2024/09/12 02:26:50 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_quotes_redirection(char *str)
{
	char	*new;
	char	*tmp;
	int		i;
	char	c;

	new = safe_malloc(ft_strlen(str) + 1);
	tmp = str;
	i = 0;
	while (*tmp)
	{
		if (*tmp == '"' || *tmp == '\'')
		{
			c = *tmp;
			tmp++;
			while (*tmp != c)
				new[i++] = *(tmp++);
			tmp++;
		}
		else
			new[i++] = *(tmp++);
	}
	new[i] = '\0';
	return (new);
}

void	here_doc_expand(t_redirection *node)
{
	char	*hold;

	hold = node->file_limiter;
	node->file_limiter = rm_quotes_redirection(node->file_limiter);
	free(hold);
}

int	not_here_doc_expand(t_redirection *node, char **env)
{
	char	*tmp;
	char	*old;
	char	**hold;

	old = ft_strdup(node->file_limiter);
	tmp = node->file_limiter;
	node->file_limiter = expand_and_leave_quotes(tmp, env);
	hold = ft_split_with_white_spaces(node->file_limiter);
	if (how_many_strings(hold) != 1)
	{
		printf("minishell: %s: ambiguous redirect\n", old);
		return (free_matrix(hold), free(old), -1);
	}
	free(node->file_limiter);
	node->file_limiter = rm_quotes_redirection(*hold);
	return (free_matrix(hold), free(old), 0);
}

int	expand_redirection(t_redirection *head, char **env)
{
	while (head)
	{
		if (head->redirection_type == 2)
			here_doc_expand(head);
		else
		{
			if (not_here_doc_expand(head, env))
				return (-1);
		}
		head = head->next;
	}
	return (0);
}
