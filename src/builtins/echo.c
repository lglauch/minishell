/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:04:20 by lglauch           #+#    #+#             */
/*   Updated: 2024/07/03 16:17:42 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	echo_command(t_lexer *lexer)
// {
// 	int	i;
// 	int	newline;

// 	i = 1;
// 	newline = 1;
// 	if (lexer->cmd[i] && !ft_strcmp(lexer->cmd[i], "-n"))
// 	{
// 		newline = 0;
// 		i++;
// 	}
// 	while (lexer->cmd[i])
// 	{
// 		while (lexer->cmd[i])
// 		{
// 			if (printf("%s", lexer->cmd[i++]) == -1)
// 				return (1);
// 			if (lexer->cmd[i])
// 			{
// 				if (printf(" ") == -1)
// 					return (1);
// 			}
// 		}
// 	}
// 	if (newline && printf("\n"))
// 		return (0);
// 	return (0);
// }
int	check_input(char *line, size_t i)
{
	size_t	j;

	j = i + 2;
	while (line[j] && !is_spc(line[j]))
	{
		if (line[j] != 'n')
			return (1);
		j++;
	}
	return (0);
}

void	remove_n_flag(char *line, int *index)
{
	size_t	i;
	int		flag;
	int		count;

	flag = 0;
	count = 0;
	i = *index;
	if (!line || !*line)
		return ;
	while (line[i] == '-' && line[i + 1] == 'n')
	{
		if (line[i + 2] == ' ' || line[i + 2] == 0 || line[i + 2] == 'n')
		{
			if (check_input(line, i) == 0)
			{
				i += 2;
				flag = 1;
				while (line[i] == 'n')
				{
					i++;
					count++;
				}
				if (line[i] != ' ' && line[i] != 0)
					flag = 0;
				while (flag && line[i] == ' ')
					i++;
				if (!flag)
					break ;
			}
			else
				break ;
		}
		else
			break ;
	}
	if (!flag)
		*index = i - count;
	else
		*index = i;
}

char	*transform_correct(char *line, int n)
{
	int		i;
	int		single;
	int		doubl;
	char	*new_str;
	int		j;

	i = 0;
	single = 0;
	doubl = 0;
	j = 0;
	new_str = malloc(sizeof(char) * ft_strlen(line) + 1);
	while (line[i])
	{
		while (is_spc(line[i]) && is_spc(line[i + 1]) && !single && !doubl)
			i++;
		if (n == 0)
		{
			remove_n_flag(line, &i);
			n = 1;
		}
		if (line[i] == '\"' && single == 0)
		{
			doubl = !doubl;
			new_str[j++] = line[i++];
		}
		if (line[i] == '\'' && doubl == 0)
		{
			single = !single;
			new_str[j++] = line[i++];
		}
		if ((line[i] == '>' || line[i] == '<' || line[i] == '|') && !single && !doubl)
		{
			if (line[i] == '|')
			{
				line[i] = 0;
				break ;
			}
			while (line[i] != 0 && !is_spc(line[i]))
				i++;
		}
		else
			new_str[j++] = line[i];
		i++;
	}
	new_str[j] = 0;
	return (new_str);
}

int	is_n_flag(char *str)
{
	if (str[0] != '-')
		return (0);
	str++;
	while (*str)
	{
		if (*str != 'n')
			return (0);
		str++;
	}
	return (1);
}

int	echo_command(t_lexer *lexer)
{
	int		i;
	int		newline;
	char	*line;

	i = 1;
	newline = 1;
	if (lexer->cmd[i] && is_n_flag(lexer->cmd[i]))
	{
		newline = 0;
		i++;
	}
	line = *last_line();
	line += 4;
	while (is_spc(*line))
		line++;
	line = transform_correct(line, newline);
	if (line && remove_quotes(line))
		printf ("%s", line);
	if (newline && printf("\n"))
		return (0);
	return (0);
}
