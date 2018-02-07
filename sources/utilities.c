/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/12 09:25:59 by acottier          #+#    #+#             */
/*   Updated: 2016/08/18 13:57:29 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		issep(char c)
{
	if (c == ' ' || c == '\t')
		return (0);
	if (c == '&')
		return (1);
	if (c == '|')
		return (2);
	if (c == ';')
		return (3);
	return (-1);
}

int		get_next_sep(char *command)
{
	int		sep;
	int		semicolon;

	if (ft_strlenchr(command, '&') < ft_strlenchr(command, '|'))
		sep = ft_strlenchr(command, '&');
	else
		sep = ft_strlenchr(command, '|');
	semicolon = ft_strlenchr(command, ';');
	if (sep < semicolon)
		return (sep);
	return (semicolon);
}

int		get_next_space(char *command)
{
	int		space;
	int		tab;

	space = ft_strlenchr(command, ' ');
	tab = ft_strlenchr(command, '\t');
	if (space < tab)
		return (space);
	return (tab);
}

int		is_full_sep(char *str, int i)
{
	if (!str[i] || str[i] == '\0')
		return (0);
	if ((str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '|' && str[i + 1] == '|')
			|| str[i] == ';' || str[i] == '\0')
		return (1);
	return (0);
}

void	free_input_list(t_input *lnk)
{
	t_input	*swap;

	if (!lnk)
		return ;
	while (lnk->prev)
		lnk = lnk->prev;
	while (lnk)
	{
		swap = lnk->next;
		free(lnk->command);
		ft_freetab(lnk->args);
		free(lnk);
		lnk = swap;
	}
}
