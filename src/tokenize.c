/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 10:07:51 by rchavez@stu       #+#    #+#             */
/*   Updated: 2024/07/04 14:49:25 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_spc(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' 
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	else
		return (0);
}

int	is_op(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	count_lex(char *line)
{
	int	i;
	int	last;
	int	count;

	i = 0;
	count = 0;
	last = 1;
	while(line[i])
	{
		if (is_op(line[i]))
		{
			last = 1;
			count++;
			while(line [i] && is_op(line[i]))
				i++;
			i--;
		}
		else if(!is_spc(line[i]))
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
	while(args[*j] && !is_op(args[*j][0]))
		*j += 1;
	return (*j - i);
}

int	count_ops(char **args, int *j)
{
	int	i;

	i = *j;
	while(args[*j] && is_op(args[*j][0]))
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
	// while (args[j])
	// 	printf("\nstr: '%s'\n", args[j++]);
	// j = 0;	
	if (!args)
		printf("\nPreotection Missing\n");//											FIX!
	ret = (t_lexer *)malloc(sizeof(t_lexer) * (count + 1));
	if (!ret)
		printf("\nPreotection Missing\n");//											FIX!
	while (++i < count)
	{
		ret[i].cmd = (char **)malloc(sizeof(char *) * (count_cmd(args, &j) + 1));
		if (!ret[i].cmd)
			printf("\nPreotection Missing\n");//										FIX!
		ret[i].ops = (char **)malloc(sizeof(char *) * (count_ops(args, &j) + 1));
		if (!ret[i].ops)
			printf("\nPreotection Missing\n");//										FIX!
	}
	return (token_fill(ret, args));
}

t_lexer	*token_fill(t_lexer *ret, char **args)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	z = 0;
	while (args[i])
	{
		j = 0;
		while(args[i] && !is_op(args[i][0]))
		{
			ret[z].cmd[j] = args[i];
			i++;
			j++;
		}
		ret[z].cmd[j] = NULL;
		j = 0;
		while(args[i] && is_op(args[i][0]))
		{
			ret[z].ops[j] = args[i];
			j++;
			i++;
		}
		ret[z].ops[j] = NULL;
		z++;
	}
	// path_finder(ret);
	return ret;
}

