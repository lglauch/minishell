/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchavez <rchavez@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 11:03:14 by rchavez           #+#    #+#             */
/*   Updated: 2024/06/17 12:18:01 by rchavez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# define READ O_RDONLY
# define WRITE (O_WRONLY | O_TRUNC | O_CREAT)
# define APPEND (O_WRONLY | O_APPEND | O_CREAT)
// # define HEREDOC 
# define PERMISSIONS 0644

typedef struct s_envp
{
	char			*value;
	char			*name;
	struct s_envp	*next;
}					t_envp;

typedef struct s_file
{
	char			*filename;
	int				mode;
	int				fd;
}					t_file;

typedef struct s_lexer
{
	char			**cmd;
	char			*path;
	t_file			*input;
	t_file			*output;
	int				pid;
	struct s_lexer	*next;
}					t_lexer;

//globals
int		*get_run(void);
t_envp	**get_envp(void);
int		*get_exit_status(void);
char	***ft_env(void);

//validate
char	*get_line(void);

//t_lexer
t_lexer	*init_lexer(int num);
int		count_lex(char **args);
t_lexer	*lex(char **args, int *status);
char	**add_cmd(t_lexer *lex, char *str);
int		handle_ops_open(t_lexer *lex, char **args, int *i);

//free_all
void	free_all(char *line, char **args, t_lexer *head, int errno);
void	free_lexer(t_lexer *head);

//files
t_file	*new_file(void);
void	set_file(t_file *file, char *file_n, int fd_n, int mode_n);

//io_handler
int		add_input(t_lexer *lex, char **args, int *i);
int		add_output(t_lexer *lex, char **args, int *i);
int		add_heredoc(t_lexer *lex, char **args, int *i);
int		add_pipe(t_lexer *lex);

//heredoc
int		do_heredoc(int fd, char *eof);

//execute
int		execute(t_lexer *tokens);
int		exec_do(t_lexer *temp);

//utils
int		is_spc(char c);
int		is_op(char c);
int		sep(char c);
char	*make_unclosed_quotes(char *str, int double_quotes, int single);
char	*handle_unclosed_quotes(char *str);

//utils2
char	*ft_strcpy(char *dest, char *src);
char	*ft_strncpy(char *dest, char *src, size_t len);
char	*ft_strchr(const char *s, int c);

//error handling
void	ft_error(int errno);

//split
char	**ft_split_args(char *str);
char	**ft_splitfree(char **ret, size_t i);

//signals
void	signal_handler(void);
void	handle_ctrlc(int signal);

//path
char	*path_finder(char *command, char *envp);
char	*env_get_by_name(char *name);

//envp
t_envp	*ft_create_envp(char **envp);
void	ft_free_envp(t_envp *head);
void	init_env(char **env);

//expand
char	*expand_tokens(char *str);

//builtins
int		echo_command(t_lexer *lexer);
int		write_and_check(int fd, const void *buf, size_t count);

#endif