/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:39 by asabir            #+#    #+#             */
/*   Updated: 2024/09/11 19:10:34 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	alter_var(char *new_var, int i)
{
	// free(environ[i]);
	environ[i] = ft_strdup(new_var);
}

void	change_variable(char *new_var)
{
	int		i;
	char	*key_var;
	char	*key_env;

	i = 0;
	key_var = return_key(new_var);
	while (environ[i])
	{
		key_env = return_key(environ[i]);
		if (ft_strcmp(key_env, key_var) == 0)
		{
			free(key_env);
			break ;
		}
		i++;
		free(key_env);
	}
	alter_var(new_var, i);
	free(key_var);
}

char	*parent_directory_path(char *current_dir)
{
	char	*parent_dir;
	int		size_path;
	int		max;

	parent_dir = NULL;
	if (current_dir[0] == '/' && current_dir[1] == '\0')
		return (current_dir);
	else
	{
		size_path = ft_strlen(current_dir);
		max = size_path - 1;
		while (current_dir[max] != '/')
			max--;
		parent_dir = safe_malloc(sizeof(char) * (max + 1));
		parent_dir = ft_strncpy(current_dir, parent_dir, max);
	}
	return (parent_dir);
}

void	case_go_back(t_cmd_track *c_track, int output)
{
	char	*old_env;
	char	*current_env;
	char 	*var_and_value;
	
	current_env = NULL;
	old_env = getenv("OLDPWD");
	current_env = getcwd(current_env, 0);
	c_track->cd_error_message = "minishell: cd: OLDPWD not set";
	if (chdir(old_env) == -1)
	{
		free(current_env);
		ft_putstr("bash: cd: OLDPWD not set", 2);
		c_track->exit_value = 1;
	}
	else
	{
		var_and_value = ft_join("OLDPWD=", current_env);
		ft_putstr(old_env, output);
		write(output, "\n", 1);
		free(current_env);
		change_variable(var_and_value);
		free(var_and_value);
		var_and_value = ft_join("PWD=", old_env);
		change_variable(var_and_value);
		free(var_and_value);
	}
}

void	case_go_up(t_cmd_track *c_track)
{
	(void)c_track;
	char	*current_dir;
	char	*parent_dir;

	current_dir = NULL;
	current_dir = getcwd(current_dir, 0);
	if (current_dir == NULL)
	{
		ft_putstr("error while getting the path of current directory\n", 2);
		c_track->exit_value = 1;
		return;
	}
	parent_dir = parent_directory_path(current_dir);
	if(parent_dir == NULL)
		return;
	change_directory(parent_dir, c_track, current_dir);
	free(parent_dir);
}

void	case_go_home(t_cmd_track *c_track)
{
	char	*home_dir;
	char	*current_dir;

	(void)c_track;
	current_dir = NULL;
	home_dir = getenv("HOME");
	current_dir = getcwd(current_dir, 0);
	if (current_dir == NULL)
	{
		ft_putstr("error while getting the path of current directory\n", 2);
		c_track->exit_value = 1;
		return;
	}
	if (home_dir == NULL) //it should always work
	{
		ft_putstr("minishell: cd: HOME not set ", 2);
		c_track->exit_value = 1;
	}
	else
		change_directory(home_dir, c_track, current_dir);
}

void change_directory(char *dir_to_access, t_cmd_track *c_track, char *oldpwd)
{
	char	*var_and_value;

	if (chdir(dir_to_access) == -1)
	{
		if(c_track->cd_error_message != NULL)
			ft_putstr(c_track->cd_error_message, 2);
		else
			perror("minishell: cd");
		free(oldpwd);
		c_track->exit_value = 1;
		return;
	}
	else
	{
		var_and_value = ft_join("OLDPWD=", oldpwd);
		free(oldpwd);
		change_variable(var_and_value);
		free(var_and_value);
		var_and_value = ft_join("PWD=", dir_to_access);
		change_variable(var_and_value);
		free(var_and_value);
	}
	return;
}

void directories_inside_current_directory(t_line_splited *head, t_cmd_track *c_track)
{
	char *current_dir;
	char *tmp;
	char *join;

	current_dir = NULL;
	current_dir = getcwd(current_dir, 0);
	if(current_dir == NULL)
	{
		ft_putstr("error while getting the path of current directory\n", 2);
		c_track->exit_value = 1;
		return;
	}
	else
	{
		tmp = ft_join(current_dir, "/");
		join = ft_join(tmp, head->cmd[1]);
		if(access(join , X_OK) == -1)
		{
			ft_putstr("minishell: cd", 2);
			perror(head->cmd[1]);
			c_track->exit_value = 1;
		}
		else
			(void)change_directory(join, c_track, current_dir);
		free(tmp);
		free(join);
	}
}

void	handle_absolute_paths(t_line_splited *head, t_cmd_track *c_track)
{
	char	*current_dir;
	

	current_dir = NULL;
	current_dir = getcwd(current_dir, 0);
	if (current_dir == NULL)
	{
		ft_putstr("error while getting the path of current directory\n", 2);
		c_track->exit_value = 1;
		return;
	}
	if (access(head->cmd[1], X_OK) == -1)
	{
		ft_putstr("minishell: ", 2);
		perror(head->cmd[1]);
		c_track->exit_value = 1;
	}
	else
		change_directory(head->cmd[1], c_track, current_dir);
}

// ay envirement variable kaytzad meah new line ms hana testi b \0 temporairement
void	ft_cd(t_line_splited *head, t_cmd_track	*c_track, int output)
{
	c_track->cd_error_message = NULL;
	if (head->cmd[1] == NULL || ft_strcmp(head->cmd[1], ".") == 0)
		return;
	else if (ft_strcmp(head->cmd[1], "-") == 0)
		case_go_back(c_track ,output);
	else if (ft_strcmp(head->cmd[1], "..") == 0)
		case_go_up(c_track);
	else if (ft_strcmp(head->cmd[1], "~") == 0)
		case_go_home(c_track);
	else if (ft_strchr(head->cmd[1], '/') == 0)
	{
		handle_absolute_paths(head, c_track);
	}
	else 
		directories_inside_current_directory(head, c_track);
}
