/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_files_0.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabir <asabir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 12:12:21 by asabir            #+#    #+#             */
/*   Updated: 2024/09/10 15:41:59 by asabir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	case_input(t_line_splited *head, int *outfile, int *infile)
{
	char* file_name;

	if (*infile != 0)
		close(*infile);
	*infile = open(head->redirection->file_limiter, O_RDONLY, 0744);
	if (*infile == -1)
	{
		file_name = ft_join(head->redirection->file_limiter, ": ");
		while (head->redirection)
		{
			if (head->redirection->redirection_type == 2) //input heredoc
				*infile = open_heredoc(head->redirection);
			head->redirection = head->redirection->next;
		}
		ft_putstr("minishell: ", 2);
		ft_putstr(file_name,2);
		free(file_name);
		perror(NULL);
		if (*outfile != 1)
			close(*outfile);
		return (-1);
	}
	return (0);
}

int	case_heredoc(t_line_splited *head, int *infile)
{
	int	fd;
	char *file_name;

	if (*infile != 0)
		close(*infile);
	*infile = open_heredoc(head->redirection);
	if (*infile == -1)
	{
		file_name = ft_join(head->redirection->file_limiter, ": ");
		ft_putstr("minishell: ", 2);
		ft_putstr(file_name, 2);
		free(file_name);
		perror(NULL);
		return (-1);
	}
	close(*infile);
	fd = open("heredoc", O_RDWR, 0744);
	if (fd == -1)
	{
		perror("minishell :");
		return (-1);
	}
	return (0);
}

int	case_normal_output(t_line_splited *head, int *outfile)
{
	char *file_name;

	if (*outfile != 1)
		close(*outfile);
	*outfile = open(head->redirection->file_limiter, O_CREAT | O_RDWR | O_TRUNC,
			0744);
	if (*outfile == -1)
	{
		file_name = ft_join(head->redirection->file_limiter, ": ");
		ft_putstr("minishell: ", 2);
		ft_putstr(file_name, 2);
		free(file_name);
		perror(NULL);
		return (-1);
	}
	return (0);
}

int	case_append_output(t_line_splited *head, int *outfile)
{
	char *file_name;

	if (*outfile != 1)
		close(*outfile);
	*outfile = open(head->redirection->file_limiter,
			O_CREAT | O_RDWR | O_APPEND, 0744);
	if (*outfile == -1)
	{
		file_name = ft_join(head->redirection->file_limiter, ": ");
		ft_putstr("minishell: ", 2);
		ft_putstr(file_name, 2);
		free(file_name);
		perror(NULL);
		return (-1);
	}
	return (0);
}

// if there is input file without < then others with it we take that first
int	parse_files(t_line_splited *head, int *outfile, int *infile)
{
	while (head->redirection)
	{
		if (head->redirection->redirection_type == 1) // input
		{
			if (case_input(head, outfile, infile) == -1)
				return (-1);
		}
		else if (head->redirection->redirection_type == 2) // input heredoc
		{
			if (case_heredoc(head, infile) == -1)
				return (-1);
		}
		else if (head->redirection->redirection_type == 3) // output
		{
			if (case_normal_output(head, outfile) == -1)
				return (-1);
		}
		else if (head->redirection->redirection_type == 4) // output append
		{
			if (case_append_output(head, outfile) == -1)
				return (-1);
		}
		head->redirection = head->redirection->next;
	}
	return (0);
}
