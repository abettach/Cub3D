/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:25:53 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 11:23:31 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		ft_murs_util(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_more(t_recup *recup)
{
	recup->depart = 'x';
	recup->indicateur2 = 0;
	recup->d.img = NULL;
	recup->texture[0].img = NULL;
	recup->texture[1].img = NULL;
	recup->texture[2].img = NULL;
	recup->texture[3].img = NULL;
	recup->texture[4].img = NULL;
	recup->d.mlx_win = NULL;
	recup->map = NULL;
}

void	ft_initialisation(t_recup *recup)
{
	recup->no = NULL;
	recup->so = NULL;
	recup->we = NULL;
	recup->ea = NULL;
	recup->sp = NULL;
	recup->f = 0;
	recup->c = 0;
	recup->rx = 0;
	recup->ry = 0;
	recup->nblines = 0;
	recup->sizeline = 0;
	recup->map = NULL;
	recup->multijoueurs = 0;
	recup->lignevide = 0;
	recup->insidemap = 0;
	recup->count = 0;
	recup->sum = 0;
	recup->wrongcharmap = 0;
	ft_init_more(recup);
}

void	ft_init(t_recup *recup)
{
	recup->num_rays = recup->ry;
	recup->p.facingup = 0;
	recup->p.facingdown = 0;
	recup->p.facingright = 0;
	recup->p.facingleft = 0;
	recup->p.px = recup->dx * TILE_SIZE + 32;
	recup->p.py = recup->dy * TILE_SIZE + 32;
	recup->d.forward = 0;
	recup->d.back = 0;
	recup->d.left = 0;
	recup->d.right = 0;
	recup->d.rotate_left = 0;
	recup->d.rotate_right = 0;
	if (recup->depart == 'S')
		recup->p.ang = 0;
	if (recup->depart == 'W')
		recup->p.ang = M_PI3;
	if (recup->depart == 'E')
		recup->p.ang = M_PI2;
	if (recup->depart == 'N')
		recup->p.ang = M_PI;
}

void	ft_init2(t_recup *recup)
{
	recup->p.xintercept = 0;
	recup->p.yintercept = 0;
	recup->p.xstep = 0;
	recup->p.ystep = 0;
	recup->p.horzwallhitx = 0;
	recup->p.horzwallhity = 0;
	recup->p.nexthorizontaltouchx = 0;
	recup->p.nexthorizontaltouchy = 0;
	recup->p.foundvertwallhit = 0;
	recup->p.foundhorzwallhit = 0;
	recup->p.vertwallhitx = 0;
	recup->p.vertwallhity = 0;
	recup->p.nextverticaltouchx = 0;
	recup->p.nextverticaltouchy = 0;
}
