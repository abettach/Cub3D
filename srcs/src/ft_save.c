/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:18:28 by abettach          #+#    #+#             */
/*   Updated: 2020/12/03 18:28:04 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

static void		bmp_image(t_recup *m, int fd)
{
	int y;
	int x;

	x = m->rx - 1;
	while (x >= 0)
	{
		y = 0;
		while (y < m->ry)
		{
			write(fd, &m->d.addr[x * m->ry + y], 4);
			y++;
		}
		x--;
	}
}

static void		info_header(t_recup *m, int fd)
{
	int info_header_size;
	int plane;
	int i;

	info_header_size = 40;
	plane = 1;
	write(fd, &info_header_size, 4);
	write(fd, &m->ry, 4);
	write(fd, &m->rx, 4);
	write(fd, &plane, 2);
	write(fd, &m->d.bits_per_pixel, 2);
	i = 0;
	while (i++ < 32)
		write(fd, "\0", 1);
}

static void		creat_bmp(t_recup *m)
{
	int size;
	int fd;
	int dataoffset;

	dataoffset = 54;
	fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0640);
	dataoffset = 54;
	size = dataoffset + (4 * (m->ry * m->rx));
	write(fd, "BM", 2);
	write(fd, &size, 4);
	write(fd, "\0\0\0\0", 4);
	write(fd, &dataoffset, 4);
	info_header(m, fd);
	bmp_image(m, fd);
	close(fd);
}

void			ft_save(t_recup *m)
{
	creat_bmp(m);
	ft_exit(m);
}

int				ft_check_save(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (str[i - 1] == 'e' && str[i - 2] == 'v' && str[i - 3] == 'a' &&
		str[i - 4] == 's' && str[i - 5] == '-' && str[i - 6] == '-'
		&& ft_strlen(str) < 7)
		return (1);
	else
		return (0);
}
