/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 10:44:14 by rchavez           #+#    #+#             */
/*   Updated: 2024/07/04 11:47:17 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_perror(char *s1, char *s2, char *s3)
{
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
		write(2, s2, ft_strlen(s2));
	if (s3)
		write(2, s3, ft_strlen(s3));
}

void	ft_perror_spc(char *s1, char *s2, char *s3)
{
	size_t	i;

	i = 0;
	if (s1)
		write(2, s1, ft_strlen(s1));
	if (s2)
	{
		while(s2[i] && !is_spc(s2[i]) && s2[i] != '|')
		{
			write(2, &s2[i], 1);
			i++;
		}
	}
	if (s3)
		write(2, s3, ft_strlen(s3));
}
