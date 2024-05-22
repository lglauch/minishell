/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:07:51 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/05/21 17:52:39 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_lex(char *line)
{
	int	i;
	int	last;
	int	count;

	i = 0;
	count = 0;
	last = 1;
	while (line[i])
	{
		if (is_op(line[i]))
		{
			last = 1;
			count++;
			while (line [i] && is_op(line[i]))
				i++;
			i--;
		}
		else if (!is_spc(line[i]))
			last = 0;
		i++;
	}
	if (!last)
		count++;
	return (count);
}

int	count_cmd(char **args, int *j)
{
	int	i;

	i = *j;
	while (args[*j] && !is_op(args[*j][0]))
		*j += 1;
	return (*j - i);
}

int	count_ops(char **args, int *j)
{
	int	i;

	i = *j;
	while (args[*j] && is_op(args[*j][0]))
		*j += 1;
	return (*j - i);
}

t_lexer	*tokenize(char *line)
{
	t_lexer	*ret;
	char	**args;
	int		i;
	int		j;
	int		count;

	count = count_lex(line);
	i = -1;
	j = 0;
	args = ft_split_args(line);
	if (!args)
		printf("\nPreotection Missing\n");//											FIX!
	ret = (t_lexer *)malloc(sizeof(t_lexer) * (count + 1));
	if (!ret)
		printf("\nPreotection Missing\n");//											FIX!
	while (++i < count)
	{
		ret[i].cmd = (char **)malloc(sizeof(char *)
				* (count_cmd(args, &j) + 1));
		if (!ret[i].cmd)
			printf("\nPreotection Missing\n");//										FIX!
		ret[i].ops = (char **)malloc(sizeof(char *)
				* (count_ops(args, &j) + 1));
		if (!ret[i].ops)
			printf("\nPreotection Missing\n");//										FIX!
	}
	return (token_fill(ret, args));
}

t_lexer	*token_fill(t_lexer *ret, char **args)
{
	int			i;
	int			j;
	int			z;
	char	*path;

	i = 0;
	z = 0;
	while (args[i])
	{
		j = 0;
		while (args[i] && !is_op(args[i][0]))
		{
			ret[z].cmd[j] = args[i];
			i++;
			j++;
		}
		ret[z].cmd[j] = NULL;
		j = 0;
		while (args[i] && is_op(args[i][0]))
		{
			ret[z].ops[j] = args[i];
			j++;
			i++;
		}
		ret[z].ops[j] = NULL;
		z++;
	}
	ret[z].cmd = NULL;
	z = 0;
	while (ret[z].cmd != NULL && ret[z].cmd[0] != NULL)
	{
		path = path_finder(&ret[z], ret[z].cmd[0], getenv("PATH"));
		if (!path)
		{
			printf("\nCommand not found\n");
			break ;
		}
		printf("PATH: %s\n", ret[z].path);
		z++;
	}
	return (ret);
}
