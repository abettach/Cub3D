/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_projection_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:25:32 by abettach          #+#    #+#             */
/*   Updated: 2020/12/09 13:19:55 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	ft_draw_floor_sky(t_recup *recup)
{
	int x;
	int y;

	x = -1;
	while (++x < recup->rx / 2)
	{
		y = -1;
		while (++y < recup->ry)
			recup->d.addr[(x) * recup->ry + y] = recup->c;
	}
	while (++x < recup->rx)
	{
		y = -1;
		while (++y < recup->ry)
			recup->d.addr[x * recup->ry + y] = recup->f;
	}
}

void	ft_texture_position(t_recup *recup)
{
	if (!recup->p.washitvertical && recup->p.facingup)
		recup->t.tindex = 1;
	if (!recup->p.washitvertical && !recup->p.facingup)
		recup->t.tindex = 0;
	if (recup->p.washitvertical && recup->p.facingleft)
		recup->t.tindex = 3;
	if (recup->p.washitvertical && !recup->p.facingleft)
		recup->t.tindex = 2;
}

void	ft_draw_texture(t_recup *recup)
{
	int i;
	int j;
	int x;

	i = 0;
	recup->t.walloffsety = !recup->p.washitvertical ?
	(int)recup->ly % 64 : (int)recup->lx % 64;
	x = recup->r.drawstarty < 0 ? -recup->r.drawstarty : 0;
	while (i < recup->r.walllinewidth)
	{
		j = x;
		while (j < recup->r.walllineheight &&
		recup->r.drawstarty + j < recup->rx)
		{
			recup->t.walloffsetx = j * (TEXTURE_HIGHT /
			recup->r.walllineheight);
			ft_texture_position(recup);
			recup->t.texcolor = recup->texture[recup->t.tindex].addr
			[(recup->t.walloffsetx * TEXTURE_HIGHT) + recup->t.walloffsety];
			recup->d.addr[(recup->r.drawstarty + j) * recup->ry +
			(recup->r.drawstartx + i)] = recup->t.texcolor;
			j++;
		}
		i++;
	}
}

void	ft_render3dwalls(t_recup *recup)
{
	double ang;

	ang = recup->p.ang + (FOV / 2);
	recup->r.pwalldist = (recup->ry / 2) / tan(FOV / 2);
	recup->r.walllinewidth = 1;
	recup->r.drawstartx = 0;
	while (recup->r.drawstartx < recup->num_rays)
	{
		ang = ft_normalize_ang(ang);
		recup->r.corrdist = ft_get_intersection(recup, ang) *
		cos(ang - recup->p.ang);
		recup->sdist[recup->r.drawstartx] =
		ft_get_intersection(recup, ang);
		recup->r.walllineheight = (TILE_SIZE / recup->r.corrdist) *
		recup->r.pwalldist;
		recup->r.drawstarty = (recup->rx / 2) - (recup->r.walllineheight / 2);
		ft_draw_texture(recup);
		ang -= FOV / recup->num_rays;
		recup->r.drawstartx++;
	}
	ft_sprite(recup, -1);
}
