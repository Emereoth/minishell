/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 13:07:53 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 15:31:26 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*prompt_path(t_env *env)
{
	char	*home;
	char	*pwd;
	char	*res;

	pwd = NULL;
	pwd = getcwd(pwd, 512);
	if ((home = get_env_content("HOME", env)) == NULL)
		return (ft_strdup("Home not found. Stop playing with unsetenv pls."));
	if (ft_strstr(pwd, home) != 0)
	{
		if (ft_strcmp(home, "/") == 0)
			res = ft_strjoin("~/", ft_strstr(pwd, home) + ft_strlen(home));
		else
			res = ft_strjoin("~", ft_strstr(pwd, home) + ft_strlen(home));
		free(pwd);
		free(home);
		return (res);
	}
	else
	{
		free(home);
		(pwd == NULL) ? ft_putstr("Where the fuck am I?") : 0;
		return (pwd);
	}
}

void	replace_env_commands(t_input *lst)
{
	char	**swap;

	while (lst)
	{
		if (ft_strcmp(lst->command, "env") == 0 && lst->args[1]
				&& ft_strcmp(lst->args[1], "-i") != 0)
		{
			free(lst->command);
			lst->command = ft_strdup(lst->args[1]);
			swap = ft_tabdup(lst->args + 1);
			ft_freetab(lst->args);
			lst->args = ft_tabdup(swap);
			ft_freetab(swap);
		}
		lst = lst->next;
	}
}
