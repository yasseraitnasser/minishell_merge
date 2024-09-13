/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:14:02 by asabir            #+#    #+#             */
/*   Updated: 2024/09/10 12:14:03 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_array(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	while (i < c_track->nb_pipes)
	{
		free(c_track->fd[i]);
		i++;
	}
	free(c_track->fd);
}

// void free_matrix(char **str)
// {
//     int i;

//     i = 0;
//     while(str[i])
//     {
//         free(str[i]);
//         i++;
//     }
//     free(str);
// }

void	free_all(t_cmd_track *c_track)
{
	free_array(c_track);
	// free(c_track);
}

// void free_nodes(void *pt)
// {
//     while(pt->next)
//     {

//     }
// }