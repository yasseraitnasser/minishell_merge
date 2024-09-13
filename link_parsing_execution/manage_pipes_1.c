/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_pipes_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:55 by asabir            #+#    #+#             */
/*   Updated: 2024/09/10 19:07:18 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	case_failed_parsing_files(t_cmd_track *c_track, t_line_splited **head)
{
	if (c_track->nb_pipes == 0 || !(*head)->next)
	{
		c_track->exit_value = 1;
	}
	else
		*head = (*head)->next;
}

void	case_middle_built_in(t_line_splited *head, int infile, int outfile,
		t_cmd_track *c_track)
{
	if (outfile == 1 && infile == 0)
		redirect_cmd(head, c_track->cmd_type, c_track->fd[c_track->i + 1][1],
			c_track);
	else if (outfile == 1 && infile != 0)
		redirect_cmd(head, c_track->cmd_type, c_track->fd[c_track->i + 1][1],
			c_track);
	else if (outfile != 1 && infile == 0)
		redirect_cmd(head, c_track->cmd_type, outfile, c_track);
	else
		redirect_cmd(head, c_track->cmd_type, outfile, c_track);
}

void	case_middle_executable(t_line_splited *head, int infile, int outfile,
		t_cmd_track *p_track, char *path_variable)
{
	int	pid;

	if (outfile == 1 && infile == 0)
		pid = child_process(head, p_track->fd[p_track->i][0],
				p_track->fd[p_track->i + 1][1], path_variable);
	else if (outfile == 1 && infile != 0)
		pid = child_process(head, infile, p_track->fd[p_track->i + 1][1],
				path_variable);
	else if (outfile != 1 && infile == 0)
		pid = child_process(head, p_track->fd[p_track->i][0], outfile,
				path_variable);
	else
		pid = child_process(head, infile, outfile, path_variable);
	free(path_variable);
	(void)pid;
}

void	case_middle(t_line_splited *head, t_cmd_track *c_track, int infile,
		int outfile)
{
	char	*path_variable;

	path_variable = NULL;
	c_track->cmd_type = cmdType(head);
	if (c_track->cmd_type == 0)
	{
		if (search_cmd(head->cmd[0], &path_variable, c_track) == -1)
		{
			return ;
		}
		case_middle_executable(head, infile, outfile, c_track, path_variable);
	}
	else
		case_middle_built_in(head, infile, outfile, c_track);
}

void	case_last(t_line_splited *head, t_cmd_track *c_track, int infile,
		int outfile)
{
	char *path_variable;
	int cmd_type;
	int pid;
	int status;

	cmd_type = cmdType(head);
	if (cmd_type != 0)
		redirect_cmd(head, cmd_type, outfile, c_track);
	else
	{
		if (search_cmd(head->cmd[0], &path_variable, c_track) == -1)
		{
			return ;
		}
		if (infile == 0)
			pid = child_process(head, c_track->fd[c_track->i][0], outfile,
					path_variable);
		else
		{
			pid = child_process(head, infile, outfile, path_variable);
			free(path_variable);
		}
		waitpid(pid, &status, 0);
		c_track->exit_value = status >> 8;
	}
}