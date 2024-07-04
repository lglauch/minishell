/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:09:53 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/28 14:17:29 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(int errno)
{
	if (errno == -1)
		write(2, "CANNOT ALLOCATE MEMORY.\n", 24);
	else if (errno == -2)
		write(2, "FORK: MEMORY EXHAUSTED.\n", 24);
	else if (errno == -3)
		write(2, "DUP2: CANNOT REDIRECT INPUT/OUTPUT.\n", 36);
	else if (errno == -4)
		write(2, "EXECVE: FAILED TO REPLACE PROCESS.\n", 35);
	else if (errno == -5)
		write(2, "PIPE: MEMORY EXHAUSTED.\n", 24);
	// ft_free_envp(*get_envp());
	exit(*get_exit_status());
}
