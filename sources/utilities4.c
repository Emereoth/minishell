/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/20 19:31:39 by acottier          #+#    #+#             */
/*   Updated: 2016/08/31 15:56:27 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		shlvl(t_env *env, int nb)
{
	char	*content;
	char	*new_content;
	int		shlvl;
	int		output;

	if (((content = get_env_content("SHLVL", env)) == NULL))
		return (1);
	shlvl = ft_atoi(content);
	shlvl += nb;
	new_content = ft_itoa(shlvl);
	if ((output = change_env_line("SHLVL", new_content, env)) == 1)
		error(NULL, 6);
	free(content);
	free(new_content);
	return (output);
}

int		ft_exit(t_input *lst, t_env **env, char *start, int null)
{
	int		output;

	if (ft_tabsize(lst->args) > 2)
	{
		error(NULL, 4);
		return (2);
	}
	output = 0;
	if (lst->args[1])
		output = ft_atoi(lst->args[1]);
	free_input_list(lst);
	if (start)
		free(start);
	if (null == 0)
		free_env_list(*env);
	exit(output);
}

void	free_shit(char *curr_pwd, char *buff, char *dest)
{
	free(curr_pwd);
	free(buff);
	free(dest);
}

int		check_dir(char *dir)
{
	struct stat	buff;

	if (stat(dir, &buff) == -1)
	{
		free(dir);
		error(dir, 2);
		return (1);
	}
	if (S_ISDIR(buff.st_mode) == 0)
	{
		free(dir);
		error(dir, 12);
		return (2);
	}
	return (0);
}

char	*abs_path(t_input *lst, t_env *env)
{
	char	*res;
	char	*swap;

	if (!lst->args[1])
	{
		if ((res = get_env_content("HOME", env)) == NULL)
			error(NULL, 6);
	}
	else if (lst->args[1][0] == '/')
		return (ft_strdup(lst->args[1]));
	else
	{
		if ((swap = get_env_content("PWD", env)) == NULL)
			error(NULL, 6);
		res = ft_trijoin(swap, "/", lst->args[1]);
		free(swap);
	}
	return (res);
}
