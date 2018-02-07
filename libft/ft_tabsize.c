/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/13 12:11:02 by acottier          #+#    #+#             */
/*   Updated: 2016/09/01 17:57:43 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_tabsize(char **tab)
{
	char	*cursor;
	int		res;

	res = 0;
	cursor = tab[0];
	while (cursor != NULL)
	{
		res++;
		cursor = tab[res];
	}
	return (res);
}
