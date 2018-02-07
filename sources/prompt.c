/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 15:05:07 by acottier          #+#    #+#             */
/*   Updated: 2016/09/19 10:47:26 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char		*quote(void)
{
	char	*swap;
	char	*res;

	swap = NULL;
	ft_putstr(YELLOW);
	ft_putstr("quote> ");
	ft_putstr(NC);
	get_next_line(0, &swap);
	res = ft_strjoin(swap, "\n");
	free(swap);
	return (res);
}

static	int			check_quotes(char *str)
{
	t_chain		*chain;

	chain = NULL;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			if (chain && (chain->lastquote == *str))
				chain = rmv_chain(chain);
			else
				chain = add_chain(chain, *str);
		}
		str++;
	}
	if (chain != NULL)
	{
		free_chain_list(chain);
		return (1);
	}
	return (0);
}

static	void		header(t_env *env, char *logname)
{
	char	*timer;
	char	*pwd;
	time_t	t;

	(!logname) ? (logname = ft_strdup("Anonymous")) : 0;
	time(&t);
	timer = ctime(&t);
	timer = ft_strsub(timer, 11, 8);
	ft_putstr(GREEN);
	ft_putstr("[ ");
	ft_putstr(YELLOW);
	ft_putstr(timer);
	ft_putstr(GREEN);
	ft_putstr(" ] ");
	ft_putstr("[ ");
	ft_putstr(YELLOW);
	ft_putstr(logname);
	ft_putstr("@KebabShell: ");
	pwd = prompt_path(env);
	(pwd) ? ft_putstr(pwd) : 0;
	ft_putstr(GREEN);
	ft_putstr(" ]\n");
	free(logname);
	free(timer);
	free(pwd);
}

static	char		*get_line(t_env *env)
{
	char		*line;
	char		*swap;
	char		*swap2;
	int			i;

	line = NULL;
	header(env, get_env_content("LOGNAME", env));
	ft_putstr(GREEN);
	ft_triplestr("$>", NC, " ");
	get_next_line(0, &line);
	while (check_quotes(line) != 0)
	{
		swap2 = quote();
		swap = ft_strjoin(line, swap2);
		free(swap2);
		free(line);
		line = ft_strdup(swap);
		free(swap);
	}
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	swap = ft_strdup(line + i);
	free(line);
	return (swap);
}

int					prompt(char **environ, int backup)
{
	t_env		*my_env;
	char		*line;
	char		*swap;

	my_env = tab_to_chain(environ);
	while (1)
	{
		line = get_line(my_env);
		swap = line;
		parse(line, &my_env, swap);
	}
	if (backup == 1)
		ft_freetab(environ);
	free_env_list(my_env);
	return (1);
}
