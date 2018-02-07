/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathlist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/16 17:16:57 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 12:48:24 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_path		*add_link(char *allpaths, t_path *pathlist)
{
	t_path	*res;

	res = (t_path *)malloc(sizeof(t_path));
	res->prev = pathlist;
	res->next = NULL;
	if (pathlist)
		pathlist->next = res;
	if ((res->path = ft_strdupchr(allpaths, ':')) == NULL)
		res->path = ft_strdup(allpaths);
	return (res);
}

t_path				*ft_pathlist(t_env *environ, t_path **start)
{
	char		*allpaths;
	char		*cursor;
	int			i;
	t_path		*res;

	i = 0;
	res = NULL;
	if ((allpaths = get_env_content("PATH", environ)) == NULL)
		return (NULL);
	cursor = allpaths;
	while (cursor)
	{
		res = add_link(cursor, res);
		cursor = ft_strchr(cursor, ':');
		if (cursor)
			cursor++;
	}
	free(allpaths);
	while (res->prev)
		res = res->prev;
	*start = res;
	return (res);
}
