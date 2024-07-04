/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 08:44:18 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/04 11:54:46 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	execute(t_lexer *tokens)
{
	t_lexer	*temp;
	int		status;

	temp = tokens;
	while (temp)
	{
		if (temp->cmd && *get_exit_status() != 130)
			status = exec_do(temp);
		if (*get_exit_status() == 130)
			*get_exit_status() = 1;
		if (temp->input)
			close(temp->input->fd);
		if (temp->output)
			close(temp->output->fd);
		if (status < 0)
			return (status);
		temp = temp->next;
	}
	temp = tokens;
	while (temp)
	{
		if (temp->pid != 0)
			waitpid(temp->pid, get_exit_status(), 0);
		temp = temp->next;
	}
	return (0);
}

int	replace_io(t_lexer *temp)
{
	if (!is_forkable(temp))
		return (0);
	if (temp->input)
	{
		if (dup2(temp->input->fd, STDIN_FILENO) < 0)
			return (-3);
		close(temp->input->fd);
	}
	if (temp->output)
	{
		if (dup2(temp->output->fd, STDOUT_FILENO) < 0)
			return (-3);
		close(temp->output->fd);
		if (!ft_strcmp(temp->output->filename, "PIPE")
			&& !ft_strcmp(temp->next->input->filename, "PIPE"))
			close(temp->next->input->fd);
	}
	return (0);
}

int	say_not_found(t_lexer *temp)
{
	if (temp->cmd[0][0] == '/' || temp->cmd[0][0] == '.')
	{
		if (access(temp->cmd[0], F_OK) == 0)
			ft_perror(temp->cmd[0], " : Permission denied\n", NULL);
		else
			ft_perror(temp->cmd[0], " : no such file or directory\n", NULL);
	}
	else
		ft_perror(temp->cmd[0], " : command not found\n", NULL);
	*get_exit_status() = 127;
	return (0);
}

int	exec_do(t_lexer *temp)
{
	if ((!temp->cmd[0][0]) || (!ft_strncmp(temp->path, "not_found", 9)
		&& !ft_check_commands(temp)))
		return (say_not_found(temp));
	if ((temp->input && temp->input->fd < 0)
		|| (temp->output && temp->output->fd < 0)
		|| (!ft_strncmp(temp->path, "not_valid", 9)))
		return (0);
	if (is_forkable(temp))
		temp->pid = fork();
	if (temp->pid == 0)
	{
		signal(SIGINT, custom_handler);
		if (replace_io(temp) < 0)
			return (-3);
		if (ft_check_commands(temp))
			return (call_functions(temp));
		else if (execve(temp->path, temp->cmd, *ft_env()) < 0)
			return (-4);
	}
	else if (temp->pid < 0)
		return (-2);
	return (0);
}
