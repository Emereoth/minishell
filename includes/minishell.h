/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 19:18:19 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 15:31:13 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define RED		"\033[31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;3;33m"
# define NC			"\033[0m"

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <dirent.h>
# include "../libft/libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <time.h>

typedef	struct	s_path
{
	char			*path;
	struct s_path	*next;
	struct s_path	*prev;
}				t_path;

typedef	struct	s_input
{
	char			*command;
	char			**args;
	char			sep;
	struct s_input	*next;
	struct s_input	*prev;
}				t_input;

typedef	struct	s_quotes
{
	int				single;
	int				dual;
}				t_quotes;

typedef	struct	s_chain
{
	char			lastquote;
	struct s_chain	*next;
	struct s_chain	*prev;
}				t_chain;

typedef	struct	s_env
{
	char			*entry;
	char			*content;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

/*
** PROMPT.C
*/
int				prompt(char **environ, int backup);

/*
** PARSE.C
*/
void			parse(char *input, t_env **env, char *start);

/*
** REPLACE_ENV_COMMANDS.C
*/
void			replace_env_commands(t_input *lst);
char			*prompt_path(t_env *env);

/*
** SYNTAX.C
*/
void			syntax(t_input *lst, t_env **env, char *start);
int				null_env(t_input *lst, char *start, t_env *env);
int				do_link(t_input *lst, t_env **env, char *start, int null);

/*
** ENV_ADVANCED.C
*/
int				env_advanced(t_env *env, t_input *lst, int null, char *start);

/*
** BUILTINS.C
*/
int				builtins(t_input *lst, t_env **env, char *start, int null);

/*
** ENV_MODIFY.C
*/
int				ft_setenv(t_env **env, t_input *lst);
int				ft_unsetenv(t_env **env, t_input *lst, int null);
void			capitalize(char *str);

/*
** BINARY_CHECK.C
*/
int				binary_check(t_input *lst, t_env *env, int null);
int				execute(char *command, t_input *lst, char **environ, int null);

/*
** PATHLIST.C
*/
t_path			*ft_pathlist(t_env *environ, t_path **start);

/*
** ENV_CONVERSION.C
*/
t_env			*tab_to_chain(char **env);
char			**chain_to_tab(t_env *my_env);
void			free_env_list(t_env *lst);

/*
** SHELL_TERMS.C
*/
char			*shell_terms(char *input, t_env *env);

/*
** ERROR.C
*/
void			error(char *str, int errnum);

/*
** UTILITIES.C
*/
int				issep(char c);
int				get_next_sep(char *command);
int				get_next_space(char *command);
int				is_full_sep(char *str, int i);
void			free_input_list(t_input *lnk);

/*
** UTILITIES2.C
*/
int				count_args(char *str);
char			*get_last_param(char *str);
t_chain			*add_chain(t_chain *lst, char quote);
t_chain			*rmv_chain(t_chain *lst);
void			free_chain_list(t_chain *lst);

/*
** UTILITIES3.C
*/
int				get_expression(char *str);
char			*trim_quotes(char *str);
int				is_in_quotes(char *str, int i);
int				change_env_line(char *entry, char *line, t_env *env);
char			*get_env_content(char *entry, t_env *env);

/*
** UTILITIES4.C
*/
int				shlvl(t_env *env, int nb);
int				ft_exit(t_input *lst, t_env **env, char *start, int null);
void			free_shit(char *curr_pwd, char *buff, char *dest);
char			*abs_path(t_input *lst, t_env *env);
int				check_dir(char *dir);

/*
** UTILITIES5.C
*/
int				dir_swap(t_env *env);
#endif
