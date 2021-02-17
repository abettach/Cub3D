/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:42:03 by abettach          #+#    #+#             */
/*   Updated: 2020/12/09 13:11:02 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	ft_horizontale_intersection3(t_recup *recup)
{
	if (haswallat(recup, recup->p.nexthorizontaltouchx - (recup->p.
	facingup ? 1 : 0), recup->p.nexthorizontaltouchy) == '1')
	{
		recup->p.foundhorzwallhit = 1;
		recup->p.horzwallhitx = recup->p.nexthorizontaltouchx;
		recup->p.horzwallhity = recup->p.nexthorizontaltouchy;
	}
	else
	{
		recup->p.nexthorizontaltouchx += recup->p.xstep;
		recup->p.nexthorizontaltouchy += recup->p.ystep;
	}
}

void	ft_horizontale_intersection2(t_recup *recup)
{
	while (recup->p.nexthorizontaltouchy >= 0 &&
	recup->p.nexthorizontaltouchy <= recup->sizeline * 64 &&
	recup->p.nexthorizontaltouchx >= 0 &&
	recup->p.nexthorizontaltouchx <= recup->nblines * 64)
	{
		ft_horizontale_intersection3(recup);
		if (recup->p.foundhorzwallhit)
			break ;
	}
}

double	ft_horizontale_intersection1(t_recup *recup, double ang)
{
	ft_init2(recup);
	recup->p.xintercept = floor(recup->p.px / TILE_SIZE) * TILE_SIZE;
	recup->p.xintercept += recup->p.facingdown ? TILE_SIZE : 0;
	recup->p.yintercept = recup->p.py + ((recup->p.px -
	recup->p.xintercept) * -tan(ang));
	recup->p.xstep = TILE_SIZE;
	recup->p.xstep *= recup->p.facingup ? -1 : 1;
	recup->p.ystep = TILE_SIZE * -tan(ang);
	recup->p.ystep *= (recup->p.facingleft &&
	recup->p.ystep > 0) ? -1 : 1;
	recup->p.ystep *= (recup->p.facingright &&
	recup->p.ystep < 0) ? -1 : 1;
	recup->p.nexthorizontaltouchx = recup->p.xintercept;
	recup->p.nexthorizontaltouchy = recup->p.yintercept;
	ft_horizontale_intersection2(recup);
	recup->hx = recup->p.horzwallhitx;
	recup->hy = recup->p.horzwallhity;
	if (recup->p.foundhorzwallhit)
	{
		return (dist(recup->p.px, recup->p.py,
		recup->p.horzwallhitx, recup->p.horzwallhity));
	}
	return (NUM_MAX);
}

double	ft_get_intersection(t_recup *recup, double ang)
{
	double h_d;
	double v_d;

	ang = ft_normalize_ang(ang);
	ft_player_look(recup, ang);
	recup->p.washitvertical = 0;
	h_d = ft_horizontale_intersection1(recup, ang);
	v_d = ft_verticale_intersection1(recup, ang);
	if (v_d > h_d)
	{
		recup->lx = recup->hx;
		recup->ly = recup->hy;
		return (h_d);
	}
	else
	{
		recup->p.washitvertical = 1;
		recup->lx = recup->p.vertwallhitx;
		recup->ly = recup->p.vertwallhity;
		return (v_d);
	}
	return (0);
}
