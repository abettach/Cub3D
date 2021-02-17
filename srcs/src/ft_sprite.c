/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 11:14:18 by abettach          #+#    #+#             */
/*   Updated: 2020/12/01 13:54:01 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

double	dist(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	ft_snorm(double ang)
{
	if (ang < -M_PI)
		ang += (2. * M_PI);
	if (ang > M_PI)
		ang -= (2. * M_PI);
	return (ang);
}

void	ft_s_swap(t_recup *recup, int i)
{
	double tmp;
	double tmpang;

	tmp = recup->s.dist[i];
	recup->s.dist[i] = recup->s.dist[i + 1];
	recup->s.dist[i + 1] = tmp;
	tmpang = recup->s.ang[i];
	recup->s.ang[i] = recup->s.ang[i + 1];
	recup->s.ang[i + 1] = tmpang;
}

void	ft_draw_sprite(t_recup *recup, int x, int i, int j)
{
	int y;
	int sp;
	int index;

	recup->s.drawstarty = (int)(recup->ry * (0.5 - recup->s.ang[x] / FOV)
	- (recup->s.w[x] * 0.5));
	recup->s.drawstartx = (int)((recup->rx * 0.5) - (recup->s.h[x] * 0.5));
	y = recup->s.drawstartx < 0 ? abs(recup->s.drawstartx) - 1 : -1;
	i = recup->s.drawstarty < 0 ? abs(recup->s.drawstarty) - 1 : -1;
	while (++i < recup->s.w[x] && recup->s.drawstarty + i < recup->ry)
	{
		j = y;
		while (++j < recup->s.h[x] && recup->s.drawstartx + j < recup->rx)
			if (recup->s.dist[x] < recup->sdist[recup->s.drawstarty + i])
			{
				sp = 64 * (int)(64 * j / recup->s.h[x]) + i /
				recup->s.w[x] * 64;
				index = (recup->s.drawstartx + j) *
				recup->ry + recup->s.drawstarty + i;
				(recup->d.addr[index] = recup->texture[4].addr[sp] != 0 ?
				recup->texture[4].addr[sp] : recup->d.addr[index]);
			}
	}
}

void	ft_sprite(t_recup *recup, int i)
{
	while (++i < recup->s.nbspr)
	{
		recup->s.dist[i] = dist(recup->sxy[i].x, recup->sxy[i].y,
		recup->p.px, recup->p.py);
		recup->s.ang[i] = acos((recup->sxy[i].x - recup->p.px)
		/ recup->s.dist[i]);
		recup->s.ang[i] = recup->sxy[i].y - recup->p.py < 0 ?
		ft_snorm(-(recup->s.ang[i] + recup->p.ang)) :
		ft_snorm(recup->s.ang[i] - recup->p.ang);
	}
	i = -1;
	while (++i < recup->s.nbspr)
		if (recup->s.dist[i] < recup->s.dist[i + 1])
			ft_s_swap(recup, i);
	i = -1;
	while (++i < recup->s.nbspr)
	{
		recup->s.h[i] = recup->rx * SPRITE_HIEGHT / recup->s.dist[i];
		recup->s.w[i] = recup->ry * SPRITE_WIDTH / recup->s.dist[i];
		ft_draw_sprite(recup, i, 0, 0);
	}
}
