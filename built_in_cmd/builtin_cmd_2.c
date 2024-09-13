/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:43 by asabir            #+#    #+#             */
/*   Updated: 2024/09/11 19:03:28 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*return_value_env_if_exists(char *key)
{
	int		i;
	int		j;
	int		z;
	char	*value;
	char	*key_env;

	value = NULL;
	i = 0;
	j = 0;
	z = 0;
	while (environ[i])
	{
		key_env = return_key(environ[i]);
		if (ft_strcmp(key_env, key) == 0)
		{
			value = safe_malloc(sizeof(char) * ft_strlen(environ[i]));
			while (environ[i][j] && environ[i][j] != '=')
				j++;
			j++;
			while (environ[i][j])
				value[z++] = environ[i][j++];
			value[z] = '\0';
			free(key_env);
			return (value);
		}
		free(key_env);
		i++;
	}
	return (value);
}

// handle printing an envirment variable
void	ft_echo(t_line_splited *head, int fd, t_cmd_track *c_track)
{
	int	i;

	i = 1;
	if (head->cmd[1] == NULL)
		write(fd, "\n", 1);
	else if (ft_strcmp(head->cmd[1], "$?") == 0)
		printf("%d\n", c_track->exit_value);
	else if (ft_strcmp(head->cmd[1], "-n") == 0)
	{
		if (head->cmd[2] != NULL)
		{
			i++;
			while (head->cmd[i])
			{
				ft_putstr(head->cmd[i], fd);
				if (head->cmd[i + 1])
					write(fd, " ", 1);
				i++;
			}
		}
	}
	else
	{
		while (head->cmd[i])
		{
			ft_putstr(head->cmd[i], fd);
			if (head->cmd[i + 1])
				write(fd, " ", 1);
			i++;
		}
		write(fd, "\n", 1);
	}
}

void	ft_env(int fd)
{
	int	i;

	i = 0;
	while (environ[i])
	{
		ft_putstr(environ[i], fd);
		// if (environ[i + 1])
			write(fd, "\n", 1);
		i++;
	}
}

void	ft_pwd(int fd)
{
	char	*value_pwd;

	if (environ == NULL)
	{
		//! PWD IS UNSET
	}
	value_pwd = return_value_env_if_exists("PWD");
	if (value_pwd == NULL)
	{
		//! PWD IS UNSET
	}
	else
	{
		ft_putstr(value_pwd, fd);
		write(fd, "\n", 1);
	}
	free(value_pwd);
}

void	ft_unset(t_line_splited *head)
{
	int		i;
	int		check;
	char	*key_env;
	int		j;
	int		z;

	z = 1;
	while (head->cmd[z])
	{
		i = 0;
		j = 0;
		check = 0;
		while (environ[i])
		{
			key_env = return_key(environ[i]);
			if (ft_strcmp(key_env, head->cmd[z]) == 0)
			{
				check = 1;
				free(key_env);
				break ;
			}
			free(key_env);
			i++;
		}
		if (check == 1)
		{
			while (environ[j])
			{
				if (i == j)
				{
					while (environ[j + 1])
					{
						environ[j] = environ[j + 1];
						j++;
					}
					environ[j] = NULL;
					break ;
				}
				j++;
			}
		}
		z++;
	}
}

void	ft_exit(void)
{
}
