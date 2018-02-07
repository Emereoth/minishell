/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_terms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 18:29:08 by acottier          #+#    #+#             */
/*   Updated: 2016/08/31 12:32:20 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	int		check_variables(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (str[i + 1] && issep(str[i]) == -1))
			return (1);
		i++;
	}
	return (0);
}

static	int		get_next_dollar(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

static	char	*swap_shit(char *str, char *content, int i)
{
	char	*swap;
	char	*res;
	int		j;

	swap = ft_strdupchr(str, '$');
	res = ft_strjoin(swap, content);
	free(content);
	free(swap);
	j = ft_smallest(get_next_space(str + i), get_next_dollar(str + i));
	swap = ft_strdup(str + j + i);
	content = ft_strjoin(res, swap);
	free(res);
	free(swap);
	res = ft_strdup(content);
	free(content);
	return (res);
}

static	char	*replace_variables(char *str, t_env *env)
{
	char	*content;
	char	*res;
	char	*entry;
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = ft_smallest(get_next_space(str + i), get_next_dollar(str + i));
			entry = ft_strndup(str + i, j);
			ft_capitalize(entry);
			content = get_env_content(entry, env);
			free(entry);
			res = swap_shit(str, content, i);
			free(str);
			return (res);
		}
		i++;
	}
	return (str);
}

char			*shell_terms(char *input, t_env *env)
{
	char	*res;
	char	*home;
	char	*cursor;
	char	*swap;

	cursor = input;
	if (ft_strchr(input, '~') != 0 && (home = get_env_content("HOME", env)))
	{
		res = ft_strdupchr(input, '~');
		swap = ft_strjoin(res, home);
		free(res);
		cursor += ft_strlenchr(input, '~') + 1;
		res = ft_strjoin(swap, cursor);
		free(home);
		free(swap);
	}
	else
		res = ft_strdup(input);
	free(input);
	while (check_variables(res) != 0)
		res = replace_variables(res, env);
	return (res);
}
