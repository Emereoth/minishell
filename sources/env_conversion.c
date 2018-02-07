/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 10:42:26 by acottier          #+#    #+#             */
/*   Updated: 2016/08/18 14:18:19 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_env	*add_link(char *str, t_env *prev, t_env *next)
{
	t_env	*res;

	res = (t_env *)malloc(sizeof(t_env));
	res->prev = prev;
	res->next = next;
	if (res->prev)
		res->prev->next = res;
	res->entry = ft_strndup(str, ft_strlenchr(str, '='));
	res->content = ft_strdup(str + ft_strlenchr(str, '=') + 1);
	return (res);
}

void			free_env_list(t_env *lst)
{
	t_env	*swap;

	while (lst)
	{
		swap = lst->next;
		free(lst->entry);
		free(lst->content);
		free(lst);
		lst = swap;
	}
}

char			**chain_to_tab(t_env *my_env)
{
	char	**res;
	t_env	*cursor;
	int		i;

	cursor = my_env;
	i = 0;
	while (cursor)
	{
		i++;
		cursor = cursor->next;
	}
	res = (char **)malloc(sizeof(char *) * i + 1);
	cursor = my_env;
	i = 0;
	while (cursor)
	{
		res[i] = ft_trijoin(cursor->entry, "=", cursor->content);
		cursor = cursor->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

t_env			*tab_to_chain(char **env)
{
	int		i;
	t_env	*res;

	i = 0;
	res = NULL;
	while (env[i])
	{
		if (!res)
			res = add_link(env[i], NULL, NULL);
		else
			res = add_link(env[i], res, NULL);
		i++;
	}
	while (res->prev)
		res = res->prev;
	return (res);
}
