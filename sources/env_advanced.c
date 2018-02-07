/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_advanced.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/22 16:07:32 by acottier          #+#    #+#             */
/*   Updated: 2016/08/31 16:59:14 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	*env_correspondance(char *entry, t_input *lst)
{
	int		i;
	char	*command;
	char	*res;

	i = 1;
	res = NULL;
	while (lst->args[i])
	{
		command = ft_strdupchr(lst->args[i], '=');
		if (ft_strcmp(entry, command) == 0)
		{
			if (res)
				free(res);
			res = ft_strdup(lst->args[i] + ft_strlenchr(lst->args[i], '=') + 1);
		}
		free(command);
		i++;
	}
	return (res);
}

static	void	command_display(t_input *lst, t_env *env, int null)
{
	int		i;
	char	*entry_swap;
	char	*content_swap;

	i = null + 1;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '=') != 0)
		{
			entry_swap = ft_strdupchr(lst->args[i], '=');
			if ((content_swap = get_env_content(entry_swap, env)) == NULL
					|| null == 1)
				ft_putendl(lst->args[i]);
			if (content_swap)
				free(content_swap);
			free(entry_swap);
		}
		i++;
	}
}

static	int		display(t_env *env, t_input *lst, int null)
{
	char	*content;
	t_env	*cursor;

	cursor = env;
	while (null == 0 && cursor)
	{
		content = env_correspondance(cursor->entry, lst);
		ft_putstr(cursor->entry);
		ft_putchar('=');
		if (content)
		{
			ft_putendl(content);
			free(content);
		}
		else
			ft_putendl(cursor->content);
		cursor = cursor->next;
	}
	command_display(lst, env, null);
	return (0);
}

static	int		env_command(t_env *env, t_input *lst, int command, int null)
{
	char	**swap;

	swap = ft_tabdup(lst->args + command);
	ft_freetab(lst->args);
	lst->args = ft_tabdup(swap);
	ft_freetab(swap);
	free(lst->command);
	lst->command = ft_strdup(lst->args[0]);
	return (do_link(lst, &env, NULL, null));
}

int				env_advanced(t_env *env, t_input *lst, int null, char *start)
{
	int	command;
	int	i;

	i = null + 1;
	command = 0;
	while (lst->args[i])
	{
		if (ft_strchr(lst->args[i], '=') == NULL
				&& ft_strcmp(lst->args[i], "env") != 0)
		{
			command = i;
			break ;
		}
		i++;
	}
	if (command == 0)
		return (display(env, lst, null));
	else if (lst->args[1] && ft_strcmp(lst->args[1], "-i") == 0)
		return (null_env(lst, start, env));
	else
		return (env_command(env, lst, command, null));
}
