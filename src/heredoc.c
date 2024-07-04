/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 11:31:18 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/04 10:54:51 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	custom_handler(int signal)
{
	(void)signal;
	printf("\n");
	*get_exit_status() = 130;
	exit(130);
}

void	exit_130(int signal)
{
	(void)signal;
	*get_exit_status() = 130;
}

int	heredoc_child(int written, char *eof, int fd)
{
	char	*line;

	g_signal = 1;
	signal(SIGINT, custom_handler);
	written = 1;
	line = readline("> ");
	while (written >= 0 && line && ft_strcmp(line, eof))
	{
		line = expand_tokens(line, 1);
		if (!line)
			return (-1);
		written = write(fd, line, ft_strlen(line));
		if (written < 0 || write(fd, "\n", 1) < 0)
		{
			write(2, "Heredoc : Failed to write.\n", 27);
			break ;
		}
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	close(fd);
	return (written);
}

int	do_heredoc(int fd, char *eof)
{
	int		written;
	int		pid;

	if (*get_exit_status() == 130)
		return (0);
	written = 0;
	signal(SIGINT, exit_130);
	pid = fork();
	if (pid == 0)
		exit (heredoc_child(written, eof, fd));
	else if (pid < 0)
		return (-1);
	else
	{
		waitpid(pid, &written, 0);
		if (written < 0)
			return (-1);
	}
	close(fd);
	signal(SIGINT, handle_ctrlc);
	return (0);
}
