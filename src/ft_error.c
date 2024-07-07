/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez@student.42heilbronn.de <rchavez    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:09:53 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/07 17:57:56 by rchavez@stu      ###   ########.fr       */
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
	exit(*get_exit_status()); // DOESNT FREE ENV
}
