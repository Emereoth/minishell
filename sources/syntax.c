/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 19:20:33 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 12:19:18 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		executable(t_input *lst, t_env *env, int null, int output)
{
	char	*curr_path;
	char	*exe_name;
	char	*full;
	char	**envtab;

	curr_path = NULL;
	curr_path = getwd(curr_path);
	exe_name = ft_strdup(lst->command);
	full = ft_trijoin(curr_path, "/", exe_name);
	free(lst->args[0]);
	lst->args[0] = ft_strdup(full);
	free(lst->command);
	lst->command = ft_strdup(full);
	if (ft_strstr(full, "./minishell") != 0)
		output = shlvl(env, 1);
	envtab = chain_to_tab(env);
	if ((output = (execute(full, lst, envtab, null)) == -1))
		error(exe_name, 2);
	free(full);
	if (ft_strstr(lst->command, "./minishell") != 0)
		shlvl(env, -1);
	free(exe_name);
	free(curr_path);
	return (output);
}

int				do_link(t_input *lst, t_env **env, char *start, int null)
{
	int		output;

	if (!lst->command)
		return (1);
	if (ft_strstr(lst->command, "./"))
		return (executable(lst, *env, null, 0));
	else if ((output = builtins(lst, env, start, null)) == 1)
	{
		output = binary_check(lst, *env, null);
		if (output == 1 && null == 0)
		{
			if (ft_strlen(lst->command) > 0)
				error(lst->command, 0);
			else
				error(NULL, 9);
			output = -1;
		}
	}
	else
	{
		while (*env && (*env)->prev)
			*env = (*env)->prev;
	}
	return (output);
}

int				null_env(t_input *lst, char *start, t_env *env)
{
	char	**swap;
	int		i;

	i = 2;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '=') == 0)
			break ;
		i++;
	}
	swap = ft_tabdup(lst->args + i);
	ft_freetab(lst->args);
	lst->args = ft_tabdup(swap);
	ft_freetab(swap);
	free(lst->command);
	if (lst->args[0])
		lst->command = ft_strdup(lst->args[0]);
	else
		return (2);
	return (do_link(lst, &env, start, 1));
}

static	t_input	*next_or(t_input *lst)
{
	while (lst && lst->prev->sep == '|')
		lst = lst->next;
	return (lst);
}

void			syntax(t_input *lst, t_env **env, char *start)
{
	int	control;

	control = 0;
	while (lst)
	{
		(control != 0) ? (lst = next_or(lst)) : 0;
		control = 0;
		while (lst && (lst->sep == 0 || lst->sep == ';'))
		{
			do_link(lst, env, start, 0);
			lst = lst->next;
		}
		while (lst && lst->sep == '&')
		{
			if (do_link(lst, env, start, 0) != 0)
				break ;
			lst = lst->next;
		}
		while (lst && lst->sep == '|' && control == 0)
		{
			if (do_link(lst, env, start, 0) == 0)
				control = 1;
			lst = lst->next;
		}
	}
}
