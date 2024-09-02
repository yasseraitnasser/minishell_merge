/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:41:54 by yait-nas          #+#    #+#             */
/*   Updated: 2024/08/22 20:16:39 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_matrix(char **line_splited)
{
	int	i;

	i = 0;
	if (!line_splited)
		return ;
	while (line_splited[i])
	{
		free(line_splited[i]);
		i++;
	}
	free(line_splited);
}

void	free_redirection_list(t_redirection *head)
{
	t_redirection	*tmp;

	while (head)
	{
		free(head->file_limiter);
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	clean_each_node(t_line_splited *node)
{
	free_matrix(node->cmd);
	free_redirection_list(node->redirection);
}

void	free_line_splited_list(t_line_splited *head)
{
	t_line_splited	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = tmp;
	}
}

void	free_everything(t_line_splited *head)
{
	t_line_splited	*tmp;

	if (!head)
		return ;
	tmp = head;
	while (tmp)
	{
		clean_each_node(tmp);
		tmp = tmp->next;
	}
	free_line_splited_list(head);
}
