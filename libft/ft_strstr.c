/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 15:19:12 by acottier          #+#    #+#             */
/*   Updated: 2016/09/05 13:03:21 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(char *s1, char *s2)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (0);
	if (s2[0] == 0)
		return (s1);
	while (s1[i] != '\0' && s2[j] != '\0')
	{
		if (s1[i] == s2[j])
		{
			while (s1[i + j] == s2[j] && s2[j] != '\0')
				j++;
			if (s2[j] == '\0')
				return (&s1[i]);
			j = 0;
		}
		i++;
	}
	return (0);
}
