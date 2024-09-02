/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yait-nas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:25:51 by yait-nas          #+#    #+#             */
/*   Updated: 2024/08/23 20:59:34 by yait-nas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstsize(t_line_splited *head)
{
	int	i;

	i = 0;
	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

int	exit_status_is_acceptable(char *str)
{
	int		i;
	char	*trimed;

	i = 0;
	if (!str[i])
		return (0);
	trimed = ft_strtrim(str, " ");
	if (!trimed[i])
		return (free(trimed), 0);
	if (trimed[i] == '+' || trimed[i] == '-')
		i++;
	while (trimed[i])
	{
		if (trimed[i] < '0' || trimed[i] > '9')
			return (free(trimed), 0);
		i++;
	}
	if (ft_strcmp(trimed, "9223372036854775807") > 0)
		return (free(trimed), 0);
	free(trimed);
	return (1);
}

void	crazy_case_has_2nd_arg(t_line_splited *head)
{
	unsigned int	status;

	if (exit_status_is_acceptable(head->cmd[2]))
	{
		if (head->cmd[3])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		printf("exit\n");
		status = ft_atou(head->cmd[2]) % 256;
		free_everything(head);
		exit(status);
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			head->cmd[2]);
		free_everything(head);
		exit(2);
	}
}

void	crazy_case(t_line_splited *head)
{
	if (head->cmd[2])
		crazy_case_has_2nd_arg(head);
	else
	{
		printf("exit\n");
		free_everything(head);
		exit(0);
	}
}

void	exit_has_args(t_line_splited *head)
{
	unsigned int	status;

	if (!ft_strcmp(head->cmd[1], "--"))
		crazy_case(head);
	else if (exit_status_is_acceptable(head->cmd[1]))
	{
		if (head->cmd[2])
		{
			printf("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		printf("exit\n");
		status = ft_atou(head->cmd[1]) % 256;
		free_everything(head);
		exit(status);
	}
	else
	{
		printf("exit\nminishell: exit: %s: numeric argument required\n",
			head->cmd[1]);
		free_everything(head);
		exit(2);
	}
}

void	crazy_case_but_there_is_more(t_line_splited *head)
{
	if (head->cmd[2])
	{
		if (exit_status_is_acceptable(head->cmd[2]))
		{
			if (head->cmd[3])
				printf("exit\nminishell: exit: too many arguments\n");
		}
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				head->cmd[2]);
		}
	}
}

void	there_is_more(t_line_splited *head)
{
	if (head->cmd[1])
	{
		if (!ft_strcmp(head->cmd[1], "--"))
			crazy_case_but_there_is_more(head);
		else if (exit_status_is_acceptable(head->cmd[1]))
		{
			if (head->cmd[2])
				printf("exit\nminishell: exit: too many arguments\n");
		}
		else
			printf("exit\nminishell: exit: %s: numeric argument required\n",
				head->cmd[1]);
	}
}

void	ft_exit(t_line_splited *head)
{
	if (ft_lstsize(head) == 1) // this should be counted earlier
	{
		if (head->cmd[1])
			exit_has_args(head);
		else
		{
			printf("exit\n");
			free_everything(head);
			exit(0);
		}
	}
	else
		there_is_more(head);
}
