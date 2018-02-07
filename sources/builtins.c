/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/11 10:44:51 by acottier          #+#    #+#             */
/*   Updated: 2016/08/31 13:19:37 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		ft_cd2(t_env *env, char *dst)
{
	char	*curr_pwd;
	char	*buff;
	int		output;

	buff = NULL;
	if (!dst || check_dir(dst) != 0)
		return (2);
	(access(dst, X_OK) == -1) ? error(dst, 10) : 0;
	(access(dst, X_OK) == -1) ? free(dst) : 0;
	if (access(dst, X_OK) == -1)
		return (2);
	if ((chdir(dst)) != 0 || ((curr_pwd = get_env_content("PWD", env)) == NULL))
	{
		error(dst, 2);
		(dst) ? free(dst) : 0;
		return (2);
	}
	output = 0;
	buff = getcwd(buff, 512);
	if ((change_env_line("OLDPWD", curr_pwd, env)) == 1
			|| (change_env_line("PWD", buff, env)) == 1)
		output = 2;
	free_shit(curr_pwd, buff, dst);
	return (output);
}

static	int		ft_cd(t_env *env, t_input *lst, int null)
{
	(ft_tabsize(lst->args) > 2) ? (error(NULL, 4)) : 0;
	if (ft_tabsize(lst->args) > 2)
		return (2);
	if ((lst->args[1] && lst->args[1][0] == '-' && !lst->args[1][1])
			|| (null == 1 && !lst->args[1]))
	{
		(null == 1) ? error(NULL, 6) : 0;
		if (null == 1 || dir_swap(env) > 0)
			return (2);
		return (0);
	}
	else
		return (ft_cd2(env, abs_path(lst, env)));
}

static	int		ft_env_display(t_env *env, t_input *lst, int null, char *start)
{
	if (null == 1)
		return (0);
	if (lst->args[1] && ft_strcmp(lst->args[1], "-i") == 0)
		return (env_advanced(env, lst, 1, start));
	if (ft_tabsize(lst->args) == 1)
	{
		while (env)
		{
			ft_putstr(env->entry);
			ft_putchar('=');
			ft_putendl(env->content);
			env = env->next;
		}
	}
	else if (ft_tabsize(lst->args) > 1)
		return (env_advanced(env, lst, null, start));
	return (0);
}

static	int		ft_echo(t_input *lst)
{
	int		i;

	i = 1;
	if (!lst->args[1])
	{
		ft_putstr("\n");
		return (0);
	}
	if (ft_strcmp(lst->args[1], "-n") == 0)
		i = 2;
	while (lst->args[i + 1])
	{
		ft_putstr(lst->args[i]);
		i++;
		ft_putchar(' ');
	}
	if (ft_strcmp(lst->args[1], "-n") == 0)
		ft_putstr(lst->args[i]);
	else
		ft_putendl(lst->args[i]);
	return (0);
}

int				builtins(t_input *lst, t_env **env, char *start, int null)
{
	if (ft_strcmp(lst->command, "exit") == 0)
		return (ft_exit(lst, env, start, null));
	else if (ft_strcmp(lst->command, "echo") == 0)
		return (ft_echo(lst));
	else if (ft_strcmp(lst->command, "env") == 0)
		return (ft_env_display(*env, lst, null, start));
	else if (ft_strcmp(lst->command, "cd") == 0)
		return (ft_cd(*env, lst, null));
	else if (ft_strcmp(lst->command, "setenv") == 0)
		return (ft_setenv(env, lst));
	else if (ft_strcmp(lst->command, "unsetenv") == 0)
		return (ft_unsetenv(env, lst, null));
	else
		return (1);
}
