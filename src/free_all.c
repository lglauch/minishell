/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 12:23:04 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/13 13:50:58 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_lexer(t_lexer *head)
{
	t_lexer	*temp;

	if (!head)
		return ;
	while (head)
	{
		temp = head;
		if (temp->cmd)
			free(temp->cmd);
		if (temp->input)
			free(temp->input);
		if (temp->output)
			free(temp->output);
		if (temp->path)
			free(temp->path);
		head = head->next;
		free(temp);
	}
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	free_line(char *line)
{
	if (!line)
		return ;
	free(line);
}

void	free_all(char *line, char **args, t_lexer *head, int errno)
{
	free_line(line);
	free_args(args);
	free_lexer(head);
	if (errno)
		ft_error(errno);
}
