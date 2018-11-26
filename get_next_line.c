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
	//5.it reads in the file into rd_buffer until a \n is met. I use ft_strjoin to "extend" ln_buffer each time and
	//  append rd_buffer to it. Honestly I cant remember why the bzeroing.. but it doesn't work without it ><
	//  I use chr as a temporary to free the old ln_buffer.
	while ((ret = read(fd, rd_buff, BUFF_SIZE)) > 0 && !ft_strchr(rd_buff, SPR))
	{
		rd_buff[ret] = '\0';
		chr = ft_strjoin(ln_buff, rd_buff);
        free(ln_buff);
        ln_buff = chr;
		ft_bzero(rd_buff, ft_strlen(rd_buff) + 1); //?
	}
	//6.I do the same for the last read since it didnt enter the loop.
	if (ret > 0)
    	{
		chr = ft_strjoin(ln_buff, rd_buff);
        free(ln_buff);
        ln_buff = chr;
    	}
	ft_bzero(rd_buff, ft_strlen(rd_buff) + 1); //?
	//7.If there's anything left in the buffer, I "copy" it into leftover.
	if ((chr = ft_strchr(ln_buff, SPR)))
	{
		if (ret > 1)
			*leftover = ft_strdup(chr + 1);
		*chr = '\0';
	}
    free(rd_buff);
	//8.Return what we've read.
	return (ln_buff);
}

int		get_next_line(const int fd, char **line)
{
	static char	*leftover;
	char        *lo_chr;
	//1.Check for any "problems".
	if (fd < 0 || !line || BUFF_SIZE < 1 || read(fd, *line, 0) == -1)
		return (-1);
	*line = ft_strnew(0);
	if (leftover)//(If there's anything left from the last read).
	{
		//2.First it adds the content of the leftover from the last call to *line.
		*line = ft_strjoin(*line, leftover);
        free(leftover);
		//3.If SPR(\n) is found in *line (since all of the leftover was copied into *line),
		//  leftover now points to what's after it, and the \n in *line turned into a \0,
		//  and it can return 1.
		if ((lo_chr = ft_strchr(*line, SPR)))
		{
			leftover = ft_strdup(lo_chr + 1);
			*lo_chr = '\0';
			return (1);
		}
    }
	//4.If there wasnt a full line in leftover, it calls read_until to read from the file.
	lo_chr = ft_strjoin(*line, read_until(fd, &leftover));
    	free(*line);
    	*line = lo_chr;
	//9.If *line is empty, then it has read the whole file.
	if (!ft_strlen(*line))
		return (0);
	//10.End.
	return (1);
}
