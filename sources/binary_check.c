/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 14:11:04 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 12:50:04 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*check_content(char *path, char *command)
{
	DIR				*current;
	struct dirent	*x;
	char			*res;

	res = NULL;
	current = opendir(path);
	if (!current)
		return (NULL);
	while ((x = readdir(current)) != NULL)
	{
		if (ft_strcmp(x->d_name, command) == 0)
		{
			res = ft_trijoin(path, "/", command);
			break ;
		}
	}
	closedir(current);
	return (res);
}

int				execute(char *command, t_input *lst, char **environ, int null)
{
	pid_t	dad;
	int		output;

	output = 0;
	dad = fork();
	if (dad > 0)
		wait(&dad);
	else
	{
		if (null == 1)
			output = execve(command, lst->args, NULL);
		else
			output = execve(command, lst->args, environ);
	}
	ft_freetab(environ);
	return (output);
}

static	void	free_pathlist(t_path *pathlist)
{
	t_path	*swap;

	while (pathlist->prev)
		pathlist = pathlist->prev;
	while (pathlist)
	{
		free(pathlist->path);
		swap = pathlist->next;
		free(pathlist);
		pathlist = swap;
	}
}

static	int		absolute_path(t_input *lst, t_env *env, int null, int output)
{
	char	**environ;
	char	*com;
	char	*path;
	char	*res;
	char	*swap;

	environ = chain_to_tab(env);
	com = ft_strrchr(lst->command, '/') + 1;
	path = ft_strndup(lst->command, ft_strlen(lst->command) - ft_strlen(com));
	if ((res = check_content(path, com)) != NULL)
	{
		swap = ft_strdup(ft_strrchr(lst->args[0], '/') + 1);
		free(lst->args[0]);
		lst->args[0] = ft_strdup(swap);
		execute(lst->command, lst, environ, null);
		free(swap);
		output = 0;
	}
	else
		output = 1;
	free(path);
	free(res);
	return (output);
}

int				binary_check(t_input *lst, t_env *env, int null)
{
	char	*res;
	t_path	*pathlist;
	t_path	*start;

	if (lst->command[0] == '/')
		return (absolute_path(lst, env, null, 0));
	if ((pathlist = ft_pathlist(env, &start)) == NULL)
		return (1);
	while (pathlist)
	{
		if ((res = check_content(pathlist->path, lst->command)) != NULL)
		{
			(ft_strstr(res, "minishell") != 0) ? shlvl(env, 1) : 0;
			execute(res, lst, chain_to_tab(env), null);
			(ft_strstr(res, "minishell") != 0) ? shlvl(env, -1) : 0;
			free(res);
			free_pathlist(pathlist);
			return (0);
		}
		pathlist = pathlist->next;
	}
	free_pathlist(start);
	return (1);
}
