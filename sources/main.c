/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 19:20:33 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 12:54:15 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*get_pwd(char *entry)
{
	char	*pwd;
	char	*res;

	pwd = NULL;
	pwd = getcwd(pwd, 512);
	res = ft_strjoin(entry, pwd);
	free(pwd);
	return (res);
}

static	char	**backup_env(void)
{
	char	**res;
	char	*paths;
	char	*paths2;

	paths = "PATH=/nfs/2015/a/acottier/.brew/bin:/usr/bin:/bin:/usr/sbin:";
	paths2 = "/sbin:/usr/local/bin:/usr/local/munki";
	res = ft_newtab(15);
	res[0] = ft_strdup("HOME=/nfs/2015/a/acottier");
	res[1] = ft_strdup("LOGNAME=acottier");
	res[2] = ft_strdup("SHLVL=1");
	res[3] = get_pwd("PWD=");
	res[4] = get_pwd("OLDPWD=");
	res[5] = ft_strdup("ZSH=/nfs/2015/a/acottier/.oh-my-zsh");
	res[6] = ft_strjoin(paths, paths2);
	res[7] = ft_strdup("PAGER=less");
	res[8] = ft_strdup("LESS=-R");
	res[9] = ft_strdup("LC_CTYPE=");
	res[10] = ft_strdup("LSCOLORS=Gxfxcxdxbxegedabagacad");
	res[11] = ft_strdup("HOMEBREW_CACHE=/tmp//Homebrew/Caches");
	res[12] = ft_strdup("HOMEBREW_TEMP=/tmp//Homebrew/Temp");
	res[13] = ft_strdup("HOMEBREW_LOCKS=/tmp//Homebrew/Locks");
	res[14] = ft_strdup("_=/usr/bin/env");
	return (res);
}

int				main(int argc, char **argv, char **environ)
{
	(void)argv;
	if (argc == 1)
	{
		if (!environ[0])
			exit(prompt(backup_env(), 1));
		else
			exit(prompt(environ, 0));
	}
	else
	{
		ft_putstr_err("Too many arguments.\n");
		exit(1);
	}
}
