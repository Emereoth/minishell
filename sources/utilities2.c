/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 13:24:17 by acottier          #+#    #+#             */
/*   Updated: 2016/08/14 14:00:22 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			count_args(char *str)
{
	int		i;
	int		k;

	k = 0;
	i = 0;
	while (str[i] && issep(str[i]) < 1)
	{
		if ((issep(str[i]) != 0) && (!str[i + 1] || (issep(str[i + 1])) == 0))
		{
			if (is_in_quotes(str, i) == 0)
				k++;
		}
		i++;
	}
	return (k + 1);
}

char		*get_last_param(char *str)
{
	char	*swap;
	char	*cursor;

	cursor = str;
	while (issep(*cursor) == 0)
		cursor++;
	swap = ft_strdup(cursor);
	return (swap);
}

t_chain		*add_chain(t_chain *lst, char quote)
{
	t_chain	*res;

	res = (t_chain *)malloc(sizeof(t_chain));
	res->lastquote = quote;
	res->prev = lst;
	if (lst)
		lst->next = res;
	res->next = NULL;
	return (res);
}

t_chain		*rmv_chain(t_chain *lst)
{
	t_chain	*swap;

	if (lst)
	{
		swap = lst->prev;
		if (lst->prev)
			lst->prev->next = NULL;
		free(lst);
		return (swap);
	}
	return (NULL);
}

void		free_chain_list(t_chain *lst)
{
	t_chain		*swap;

	while (lst)
	{
		swap = lst->prev;
		free(lst);
		lst = swap;
	}
}
