/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lglauch <lglauch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 17:51:26 by lglauch           #+#    #+#             */
/*   Updated: 2024/06/13 14:46:00 by lglauch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	intro(void)
{
	if (!isatty(fileno(stdin)))
		return ;
	printf("\033[H\033[J");
	printf("   _   _   _   _   _   _   _   _   _   \n");
	printf("  / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ / \\ \n");
	printf(" ( M | I | N | I | S | H | E | L | L )\n");
	printf("  \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \\_/ \n");
	printf("    ********************************\n");
	printf("\n    Welcome to Minishell by \033]8;;https://github.com/rodalcham"
		"\archavez\033]8;;\a && \033]8;;https://github.com/lglauch"
		"\alglauch\033]8;;\a\n\n");
	printf("    ********************************\n");
}

void	main_loop(void)
{
	char	*line;
	t_lexer	*tokens;
	char	**args;

	line = NULL;

	while (*get_run() == 1)
	{
		line = readline("🐚  ");
		while (line && !line[0])
			line = readline("🐚  ");
		if (!line)
			break ;	if (line && ft_strlen(line) > 0)
			add_history(line);
		args = ft_split_args(line);
		if (!args)
			printf("Unprotected\n");/////             							    FIX!!!	// XXX: hi
		tokens = lex(args);
		execute(tokens);
	}
}

int	main(int argc, char **argv, char **envp)
{
	argv = (void *)argv;
	if (argc != 1)
		return (1);
	*get_envp() = ft_create_envp(envp);
	// rl_catch_signals = 0;
	signal_handler();
	intro();
	main_loop();
	printf("exit\n");
	// ft_free_envp(envp_list);
	system("leaks minishell");
	return (0);
}
