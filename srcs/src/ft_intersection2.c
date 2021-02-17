/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersection2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 12:41:22 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 12:29:07 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_atoi(const char *str)
{
	int r;

	r = 0;
	while (*str == ' ' || *str == '\t' || *str == '\r' || *str == '\n'
			|| *str == '\v' || *str == '\f')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		r = (r * 10) + (*str - '0');
		str++;
	}
	return (r);
}

void	ft_verticale_intersection3(t_recup *recup)
{
	if (haswallat(recup, recup->p.nextverticaltouchx, recup->p.
	nextverticaltouchy - (recup->p.facingleft ? 0.1 : 0)) == '1')
	{
		recup->p.foundvertwallhit = 1;
		recup->p.vertwallhitx = recup->p.nextverticaltouchx;
		recup->p.vertwallhity = recup->p.nextverticaltouchy;
	}
	else
	{
		recup->p.nextverticaltouchx += recup->p.xstep;
		recup->p.nextverticaltouchy += recup->p.ystep;
	}
}

void	ft_verticale_intersection2(t_recup *recup)
{
	while (recup->p.nextverticaltouchy >= 0 &&
	recup->p.nextverticaltouchy <= recup->sizeline * 64 &&
	recup->p.nextverticaltouchx >= 0 &&
	recup->p.nextverticaltouchx <= recup->nblines * 64)
	{
		ft_verticale_intersection3(recup);
		if (recup->p.foundvertwallhit)
			break ;
	}
}

double	ft_verticale_intersection1(t_recup *recup, double ang)
{
	ft_init2(recup);
	recup->p.yintercept = floor(recup->p.py / TILE_SIZE) * TILE_SIZE;
	recup->p.yintercept += recup->p.facingright ? TILE_SIZE : 0;
	recup->p.xintercept = recup->p.px +
	((recup->p.yintercept - recup->p.py) / tan(ang));
	recup->p.ystep = TILE_SIZE;
	recup->p.ystep *= recup->p.facingleft ? -1 : 1;
	recup->p.xstep = recup->p.ystep / tan(ang);
	recup->p.nextverticaltouchx = recup->p.xintercept;
	recup->p.nextverticaltouchy = recup->p.yintercept;
	ft_verticale_intersection2(recup);
	recup->vx = recup->p.vertwallhitx;
	recup->vy = recup->p.vertwallhity;
	if (recup->p.foundvertwallhit == 1)
	{
		return (dist(recup->p.px, recup->p.py,
		recup->p.vertwallhitx, recup->p.vertwallhity));
	}
	return (NUM_MAX);
}
