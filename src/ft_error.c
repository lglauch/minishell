/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 21:09:53 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/06/28 11:38:14 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error(int errno)
{
	if (errno == -1)
		perror("\nCANNOT ALLOCATE MEMORY.\n");
	else if (errno == -2)
		perror("\nFORK: MEMORY EXHAUSTED.\n");
	else if (errno == -3)
		perror("\nDUP2: CANNOT REDIRECT INPUT/OUTPUT.\n");
	else if (errno == -4)
		perror("\nEXECVE: FAILED TO REPLACE PROCESS.\n");
	else if (errno == -5)
		perror("\nPIPE: MEMORY EXHAUSTED.\n");
	// ft_free_envp(*get_envp());
	exit(*get_exit_status());
}
