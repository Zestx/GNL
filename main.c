/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbackaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 18:07:58 by qbackaer          #+#    #+#             */
/*   Updated: 2018/11/22 20:01:29 by qbackaer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

int		main(void)
{
    int		fd;
    char	*line;

    fd = open("lorem_ipsum", O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        printf("%s|\n", line);
        free(line);
    }
    close(fd);

    return (0);
}
