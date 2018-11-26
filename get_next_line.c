/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:00:19 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/22 18:56:10 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until(const int fd, char **leftover)
{
	char	*rd_buff;
	char	*ln_buff;
	size_t	ret;
	char	*chr;

	rd_buff = ft_strnew(BUFF_SIZE);
	ln_buff = ft_strnew(0);
	chr = NULL;
	while ((ret = read(fd, rd_buff, BUFF_SIZE)) > 0 && !ft_strchr(rd_buff, SPR))
	{
		rd_buff[ret] = '\0';
		chr = ft_strjoin(ln_buff, rd_buff);
        free(ln_buff);
        ln_buff = chr;
		ft_bzero(rd_buff, ft_strlen(rd_buff) + 1); //?
	}
	if (ret > 0)
    {
		chr = ft_strjoin(ln_buff, rd_buff);
        free(ln_buff);
        ln_buff = chr;
    }
	ft_bzero(rd_buff, ft_strlen(rd_buff) + 1); //?
	if ((chr = ft_strchr(ln_buff, SPR)))
	{
		if (ret > 1)
			*leftover = ft_strdup(chr + 1);
		*chr = '\0';
	}
    free(rd_buff);
	return (ln_buff);
}

int		get_next_line(const int fd, char **line)
{
	static char	*leftover;
	char        *lo_chr;

	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, *line, 0) == -1)
		return (-1);
	*line = ft_strnew(0);
	if (leftover)
	{
		*line = ft_strjoin(*line, leftover);
        free(leftover);
		if ((lo_chr = ft_strchr(*line, SPR)))
		{
			leftover = ft_strdup(lo_chr + 1);
			*lo_chr = '\0';
			return (1);
		}
    }
	lo_chr = ft_strjoin(*line, read_until(fd, &leftover));
    free(*line);
    *line = lo_chr;
	if (!ft_strlen(*line))
		return (0);
	return (1);
}
