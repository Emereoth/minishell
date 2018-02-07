/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acottier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/06 14:57:45 by acottier          #+#    #+#             */
/*   Updated: 2016/08/01 15:46:57 by acottier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

static void		ft_swap_update(char *stock, char **swap, int *output)
{
	char	*tmp;

	if (*output == -1 || *output == 2)
		return ;
	if (ft_strlen(*swap) == 0)
	{
		*output = 1;
		if (*swap)
			free(*swap);
		if (stock)
			ft_strclr(stock);
		return ;
	}
	tmp = ft_strdup(*swap);
	free(*swap);
	stock = ft_strdup(tmp);
	free(tmp);
}

static int		ft_traitement(char **buff, char **swap, char **line)
{
	char		*tmp;
	int			length;
	int			length_chr;

	length = ft_strlen(*swap);
	length_chr = ft_strlenchr(*swap, '\n');
	if ((*swap) && length != 0)
		*swap = ft_strjoin(*swap, *buff);
	else
		*swap = ft_strdup(*buff);
	length = ft_strlen(*swap);
	length_chr = ft_strlenchr(*swap, '\n');
	if (length == length_chr)
		return (2);
	*line = ft_strdupchr(*swap, '\n');
	tmp = ft_strdup(*swap + length_chr + 1);
	free(*swap);
	*swap = ft_strdup(tmp);
	free(tmp);
	return (1);
}

static int		ft_nettoyage(char **line, char **swap, int output)
{
	char	*tmp;

	if (output == -1)
		return (-1);
	if (output == 0 && *swap[0] != '\0')
	{
		*line = ft_strdupchr(*swap, '\n');
		tmp = ft_strdup(*swap + ft_strlenchr(*swap, '\n') + 1);
		*swap = ft_strdup(tmp);
		return (1);
	}
	else if (output == 0 && *swap[0] == '\0')
	{
		ft_strclr(*swap);
		return (0);
	}
	else
		return (output);
}

int				get_next_line(int const fd, char **line)
{
	char			*buff;
	int				output;
	static char		*stock = NULL;
	char			*swap;

	if ((fd < 3 && fd != 0) || !line || fd > 256 || BUFF_SIZE < 1)
		return (-1);
	swap = stock;
	output = 2;
	buff = ft_strnew(BUFF_SIZE);
	while (output != 1 && output != 0 && output != -1)
	{
		ft_strclr(buff);
		if ((output = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		if (buff[0] == '\0' && swap == NULL)
			output = 0;
		if (output > 0)
			output = ft_traitement(&buff, &swap, line);
		output = ft_nettoyage(line, &swap, output);
		ft_swap_update(stock, &swap, &output);
	}
	(output == 0) ? free(stock) : 0;
	free(buff);
	return (output);
}
