/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yasser </var/spool/mail/yasser>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:53:39 by yasser            #+#    #+#             */
/*   Updated: 2024/10/03 10:56:24 by yasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*norminette1(char **str)
{
	(*str)++;
	return (ft_itoa(g_exit_status_value));
}

void	norminette2(char c, char *new, int *i, char **tmp)
{
	int	x;

	if (c == -1)
	{
		x = *i;
		new[x] = '"';
		(*i)++;
	}
	if (c == -2)
	{
		x = *i;
		new[x] = '\'';
		(*i)++;
	}
	(*tmp)++;
}

void	norminette3(char **str, int *i, char **new)
{
	int	tmp;

	tmp = *i;
	new[0][*i] = **str;
	(*i)++;
	(*str)++;
}
