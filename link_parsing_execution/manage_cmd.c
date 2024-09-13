/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:14:17 by asabir            #+#    #+#             */
/*   Updated: 2024/09/11 17:11:18 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cmdType(t_line_splited *head)
{
	if (ft_strcmp(head->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(head->cmd[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(head->cmd[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(head->cmd[0], "unset") == 0)
		return (4);
	else if (ft_strcmp(head->cmd[0], "export") == 0)
		return (5);
	else if (ft_strcmp(head->cmd[0], "env") == 0)
		return (6);
	else if (ft_strcmp(head->cmd[0], "exit") == 0)
		return (7);
	else
		return (0);
}

void	redirect_cmd(t_line_splited *head, int type, int outfile,
		t_cmd_track *c_track)
{
	if (type == 1)
		ft_echo(head, outfile, c_track);
	else if (type == 2)
		ft_cd(head,c_track, outfile);
	else if (type == 3)
		ft_pwd(outfile);
	else if (type == 4)
		ft_unset(head);
	else if (type == 5)
		ft_export(head, outfile);
	else if (type == 6)
		ft_env(outfile);
	else if (type == 7)
		ft_exit();
	return ;
}

int	allocate_array(t_cmd_track *c_track)
{
	int	i;

	i = 0;
	c_track->fd = safe_malloc(sizeof(int *) * (c_track->nb_pipes));
	if (c_track->fd == NULL)
	{
		c_track->exit_value = 1;
		return (-1);
	}
	while (i < c_track->nb_pipes)
	{
		c_track->fd[i] = safe_malloc(sizeof(int) * 2);
		i++;
	}
	return (0);
}
