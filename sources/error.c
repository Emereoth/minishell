/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/09 19:19:30 by acottier          #+#    #+#             */
/*   Updated: 2016/08/30 17:04:07 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static	void	error3(char *str, int errnum)
{
	ft_putstr(RED);
	if (errnum == 6)
		ft_putendl_err("KebabShell: cd: environment not set");
	else if (errnum == 7)
		ft_putendl_err("Error while overwriting environmnent variable");
	else if (errnum == 8)
		ft_putendl_err("Error while creating new environment variable");
	else if (errnum == 9)
		ft_putendl_err("KebabShell: parse error near ';'");
	else if (errnum == 10)
	{
		ft_putstr_err("KebabShell: cd: permission denied: ");
		if (str)
			ft_putendl_err(str);
	}
	else if (errnum == 11)
		ft_putendl_err("Kebabshell: setenv: forbidden character");
	else if (errnum == 12)
		ft_putendl_err("KebabShell: cd: not a directory");
	ft_putstr(NC);
}

static	void	error2(char *str, int errnum)
{
	ft_putstr(RED);
	if (errnum == 2)
	{
		ft_putstr_err("KebabShell: cd: no such file or directory: ");
		if (str)
			ft_putstr_err(str);
		ft_putstr_err("\n");
	}
	else if (errnum == 3)
		ft_putendl_err("KebabShell: cd: string not in pwd: -");
	else if (errnum == 4)
		ft_putendl_err("KebabShell: too many arguments");
	else if (errnum == 5)
		ft_putendl_err("KebabShell: too few arguments");
	ft_putstr(NC);
	if (errnum > 5)
		error3(str, errnum);
}

void			error(char *str, int errnum)
{
	int		i;

	i = 0;
	ft_putstr(RED);
	if (errnum == 0)
	{
		ft_putstr_err("KebabShell: ");
		ft_putstr_err(str);
		ft_putendl_err(": invalid command");
	}
	else if (errnum == 1)
	{
		while (str[i + 1] && str[i + 1] == str[i])
			i++;
		ft_putstr_err("KebabShell: parse error near '");
		ft_putchar_fd(*str, 2);
		if (issep(*str) == 3 || i > 2)
			ft_putchar_fd(*str, 2);
		ft_putstr_err("'\n");
	}
	ft_putstr(NC);
	if (errnum > 1)
		error2(str, errnum);
}
