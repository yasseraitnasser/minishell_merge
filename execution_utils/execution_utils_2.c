/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:57 by asabir            #+#    #+#             */
/*   Updated: 2024/09/10 12:13:58 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (0);
		i++;
	}
	return (-1);
}

char	*ft_strncpy(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] && i < n)
	{
		str2[i] = str1[i];
		i++;
	}
	str2[i] = '\0';
	return (str2);
}
