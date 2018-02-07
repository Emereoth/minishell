/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 16:57:59 by acottier          #+#    #+#             */
/*   Updated: 2016/08/22 18:41:44 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		get_expression(char *str)
{
	t_chain	*chain;
	int		close;
	int		i;

	close = 0;
	i = 0;
	chain = NULL;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			if (chain && (chain->lastquote == str[i]))
				chain = rmv_chain(chain);
			else
				chain = add_chain(chain, str[i]);
			(!chain) ? close = i : 0;
		}
		if (!chain && (str[i] == ' ' || str[i] == '\t'))
			return (i);
		i++;
	}
	if (close == 0)
		return (ft_smallest(get_next_space(str), get_next_sep(str)));
	str += close;
	return (ft_smallest(get_next_space(str), get_next_sep(str)) + close);
}

char	*trim_quotes(char *str)
{
	if (ft_strchr(str, 39) != NULL)
		str = ft_strrmv(str, 39);
	if (ft_strchr(str, 34) != NULL)
		str = ft_strrmv(str, 34);
	return (str);
}

int		is_in_quotes(char *str, int i)
{
	t_chain	*chain;
	int		res;
	int		j;

	j = 0;
	chain = NULL;
	while (str && j < i)
	{
		if (str[j] == 34 || str[j] == 39)
		{
			if (chain && (chain->lastquote == str[j]))
				chain = rmv_chain(chain);
			else
				chain = add_chain(chain, str[j]);
		}
		j++;
	}
	if (!chain || !chain->prev)
		res = 0;
	else
		res = 1;
	while (chain)
		chain = rmv_chain(chain);
	return (res);
}

int		change_env_line(char *entry, char *line, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->entry, entry) == 0)
		{
			free(env->content);
			env->content = ft_strdup(line);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

char	*get_env_content(char *entry, t_env *env)
{
	while (env)
	{
		if (env->entry && ft_strcmp(env->entry, entry) == 0)
			return (ft_strdup(env->content));
		env = env->next;
	}
	return (NULL);
}
