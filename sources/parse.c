/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 13:51:03 by acottier          #+#    #+#             */
/*   Updated: 2016/08/31 16:28:51 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	char	**fill_tab(char *command, int k, t_input *lnk)
{
	char	**res;
	char	*cursor;
	int		i;

	res = (char **)malloc(sizeof(char *) * (count_args(command) + 1));
	cursor = command;
	while (issep(*cursor) == 0)
		cursor++;
	while (issep(*cursor) < 1 && *cursor != '\0')
	{
		i = get_expression(cursor);
		res[k] = ft_strndup(cursor, i);
		if (ft_strchr(res[k], 34) != 0 || ft_strchr(res[k], 39) != 0)
			res[k] = trim_quotes(res[k]);
		k++;
		cursor += i;
		while (issep(*cursor) == 0)
			cursor++;
	}
	res[k] = NULL;
	if (is_full_sep(cursor, 0) == 1)
		lnk->sep = *cursor;
	return (res);
}

static	t_input	*add_lnk(char *command, t_input *prev)
{
	char	*cursor;
	t_input	*lnk;
	int		i;

	cursor = command;
	lnk = (t_input *)malloc(sizeof(t_input));
	while (issep(*cursor) == 0)
		cursor++;
	i = get_expression(cursor);
	lnk->command = trim_quotes(ft_strndup(cursor, i));
	lnk->prev = prev;
	if (prev)
		lnk->prev->next = lnk;
	lnk->next = NULL;
	lnk->sep = 0;
	lnk->args = fill_tab(cursor, 0, lnk);
	free(command);
	return (lnk);
}

static	t_input	*mklist(char *input, t_input *res)
{
	int		i;
	char	*cursor;

	cursor = input;
	while (*cursor)
	{
		i = 0;
		(issep(*cursor) == 0) ? (cursor += get_next_space(cursor)) : 0;
		while (issep(cursor[i]) < 1 && cursor[i] != '\0')
			i++;
		if (is_full_sep(cursor, i) == 1)
		{
			if (cursor[i] != '\0')
				(cursor[i] == ';') ? (i++) : (i += 2);
			if (!res)
				res = add_lnk(ft_strndup(cursor, i), NULL);
			else
				res = add_lnk(ft_strndup(cursor, i), res);
		}
		else if (*cursor && !cursor[i])
			res = add_lnk(get_last_param(cursor), res);
		cursor += i;
	}
	return (res);
}

static	int		command_integrity(char *input)
{
	char	*cursor;
	int		i;

	cursor = input;
	i = 0;
	while (*cursor && *(cursor + 1))
	{
		if (i != 2 && i != 0 && (issep(*cursor) < 1))
		{
			error(cursor - i, 1);
			return (1);
		}
		(issep(*cursor) > 0 && issep(*cursor) < 3) ? (i++) : (i = 0);
		if (*cursor == ';' && *(cursor + 1) == ';')
		{
			error(cursor, 1);
			return (1);
		}
		cursor++;
	}
	return (0);
}

void			parse(char *input, t_env **my_env, char *start)
{
	t_input	*lst;

	input = shell_terms(input, *my_env);
	start = input;
	if (command_integrity(input) == 0)
	{
		if (issep(*input) == 1 || issep(*input) == 2)
		{
			error(input, 1);
			free(input);
			return ;
		}
		lst = mklist(input, NULL);
		while (lst && lst->prev)
			lst = lst->prev;
		syntax(lst, my_env, start);
		free_input_list(lst);
	}
	free(input);
}
