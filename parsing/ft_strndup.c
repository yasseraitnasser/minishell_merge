/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:29:24 by yait-nas          #+#    #+#             */
/*   Updated: 2024/09/06 03:37:59 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*s2;

	i = 0;
	s2 = safe_malloc((n + 1) * sizeof(unsigned char));
	if (s2 == NULL)
		return (s2);
	while (s1[i] && i < n)
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
