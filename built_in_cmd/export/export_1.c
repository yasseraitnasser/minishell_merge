/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:13:33 by asabir            #+#    #+#             */
/*   Updated: 2024/09/10 15:46:48 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*add_non_existing_append_var(char *new_var)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = safe_malloc(ft_strlen(new_var));
	while (new_var[i])
	{
		if (new_var[i] == '+')
			i++;
		str[j] = new_var[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

void	change_value(char *new_var, int i)
{
	if (ft_strchr(new_var, '=') == -1) //! prkkk
	{
		free(environ[i]);
		environ[i] = ft_strdup(new_var);
	}
	else
	{
		free(environ[i]);
		environ[i] = ft_strdup(new_var);
	}
}

void	append_value(char *new_var, int i)
{
	char	*temp;

	temp = environ[i];
	environ[i] = ft_join(environ[i], to_append(new_var));
	free(temp);
}

void	change_or_append_var_value(char *new_var, int check)
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
	if (check == 1) // change
		change_value(new_var, i);
	else if (check == 2) // append
		append_value(new_var, i);
	free(key_var);
}
// char * handle_variable(t_line_splited* head, int output)
// {

// }

int	create_new_environ(t_line_splited *head, int size)
{
	int		i;
	int		nb;
	char	**copy;

	i = 0;
	nb = count_new_variables(head, size);
	copy = create_copy(environ, &size);
	environ = safe_malloc(sizeof(char *) * (nb + size + 1));
	while (copy[i])
	{
		environ[i] = copy[i];
		i++;
	}
	free(copy);
	return (i);
}

char	**handle_variables(t_line_splited *head)
{
	int	initial_size;
	int	index_of_next_var;
	int	check;
	int	count_added;
	int	j;
	int	duplicated_keys;

	index_of_next_var = 0;
	duplicated_keys = 0;
	count_added = 0;
	initial_size = size_env(environ);
	index_of_next_var = create_new_environ(head, initial_size);
	j = 1;
	while (head->cmd[j])
	{
		if (check_if_valid(head->cmd[j], initial_size, count_added) == 0)
			// valid
		{
			check = check_if_add_change_append(head, head->cmd[j],
					index_of_next_var, &duplicated_keys);
			if (check == 0) // add
			{
				add_var_if_not_exist(head->cmd[j], initial_size, count_added,
					check);
				count_added++;
				index_of_next_var++;
			}
			else if (check == 1) // change
			{
				change_or_append_var_value(head->cmd[j], check);
			}
			else if (check == 2) // append
			{
				change_or_append_var_value(head->cmd[j], check);
			}
			else if (check == 3)
			{
				add_var_if_not_exist(head->cmd[j], initial_size, count_added,
					check);
				count_added++;
				index_of_next_var++;
			}
		}
		else if (check_if_valid(head->cmd[j], initial_size, count_added) == -1)
			// other like * or = pr $ ...
		{
			printf("minishell: export: '%s': not a valid identifier", head->cmd[j]);
			// err_check = 1;
		}
		else if (check_if_valid(head->cmd[j], initial_size, count_added) == -3)
			//#
		{
			free_matrix(head->cmd);
			free(head);
			exit(0);
			//! remember to free all
		}
		j++;
	}
	environ[index_of_next_var] = NULL;
	return (environ);
}
