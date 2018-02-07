/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_modify.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/15 13:59:55 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 16:16:13 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	t_env	*rmv_link(t_env **lnk)
{
	t_env	*res;

	ft_bzero((*lnk)->entry, ft_strlen((*lnk)->entry));
	ft_bzero((*lnk)->content, ft_strlen((*lnk)->content));
	free((*lnk)->entry);
	free((*lnk)->content);
	if ((*lnk)->next)
		(*lnk)->next->prev = (*lnk)->prev;
	if ((*lnk)->prev)
		(*lnk)->prev->next = (*lnk)->next;
	free(*lnk);
	if ((*lnk)->next)
		res = (*lnk)->next;
	else
		res = (*lnk)->prev;
	*lnk = NULL;
	return (res);
}

static	t_env	*add_link(t_input *lst, t_env *env)
{
	t_env	*res;

	if ((res = (t_env *)malloc(sizeof(t_env))) == NULL)
		return (NULL);
	res->entry = ft_strdup(lst->args[1]);
	res->content = ft_strdup(lst->args[2]);
	while (env && env->next)
		env = env->next;
	if (env)
		env->next = res;
	res->prev = env;
	res->next = NULL;
	return (res);
}

static	int		error_check(t_input *lst)
{
	if (ft_tabsize(lst->args) > 4)
	{
		error(NULL, 4);
		return (1);
	}
	if (ft_tabsize(lst->args) < 4)
	{
		error(NULL, 5);
		return (1);
	}
	if (ft_strchr(lst->args[1], '=') != 0)
	{
		error(NULL, 11);
		return (1);
	}
	return (0);
}

int				ft_setenv(t_env **env, t_input *lst)
{
	char	*swap;

	if (error_check(lst) == 1)
		return (2);
	ft_capitalize(lst->args[1]);
	swap = get_env_content(lst->args[1], *env);
	if (swap && lst->args[3][0] == '1')
	{
		if (change_env_line(lst->args[1], lst->args[2], *env) == 1)
		{
			error(NULL, 7);
			free(swap);
			return (2);
		}
		free(swap);
	}
	else if (!swap)
	{
		if ((*env = add_link(lst, *env)) == NULL)
		{
			error(NULL, 8);
			return (2);
		}
	}
	return (0);
}

int				ft_unsetenv(t_env **env, t_input *lst, int null)
{
	t_env	*start;
	int		i;

	i = 1;
	if (null == 1 || *env == NULL)
		return (2);
	start = *env;
	while (lst->args[i])
	{
		*env = start;
		ft_capitalize(lst->args[i]);
		if (ft_strcmp(lst->args[i], (*env)->entry) == 0)
			start = (*env)->next;
		while (*env)
		{
			if (ft_strcmp(lst->args[i], (*env)->entry) == 0)
				*env = rmv_link(env);
			else
				*env = (*env)->next;
		}
		i++;
	}
	*env = start;
	return (0);
}
