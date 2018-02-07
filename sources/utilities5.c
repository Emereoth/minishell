/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/31 12:05:16 by acottier          #+#    #+#             */
/*   Updated: 2016/08/31 13:01:43 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		dir_swap(t_env *env)
{
	int		output;
	char	*old;
	char	*current;

	output = 0;
	old = get_env_content("OLDPWD", env);
	current = get_env_content("PWD", env);
	output = change_env_line("PWD", old, env);
	if (output == 1)
		error(NULL, 7);
	else
		output = 2 * change_env_line("OLDPWD", current, env);
	if (output == 2)
		error(NULL, 7);
	if (output == 0 && chdir(old) != 0)
	{
		error(old, 2);
		output = 2;
	}
	free(old);
	free(current);
	return (output);
}
