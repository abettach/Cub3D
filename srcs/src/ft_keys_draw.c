/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:25:59 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 11:18:39 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_key_press(int keycode, t_recup *recup)
{
	if (keycode == MKEY_Z)
		recup->d.forward = 1;
	else if (keycode == MKEY_S)
		recup->d.back = 1;
	else if (keycode == MKEY_D)
		recup->d.left = 1;
	else if (keycode == MKEY_A)
		recup->d.right = 1;
	else if (keycode == MROTATE_LEFT)
		recup->d.rotate_left = 1;
	else if (keycode == MROTATE_RIGHT)
		recup->d.rotate_right = 1;
	else if (keycode == MKEY_ESC)
		ft_exit(recup);
	return (1);
}

int		ft_key_release(int keycode, t_recup *recup)
{
	if (keycode == MKEY_Z)
		recup->d.forward = 0;
	else if (keycode == MKEY_S)
		recup->d.back = 0;
	else if (keycode == MKEY_D)
		recup->d.left = 0;
	else if (keycode == MKEY_A)
		recup->d.right = 0;
	else if (keycode == MROTATE_LEFT)
		recup->d.rotate_left = 0;
	else if (keycode == MROTATE_RIGHT)
		recup->d.rotate_right = 0;
	else if (keycode == MKEY_ESC)
		ft_exit(recup);
	return (1);
}

void	ft_forward_back(t_recup *recup)
{
	if (recup->d.forward == 1)
	{
		if (recup->map[(int)(recup->p.px + cos(recup->p.ang) *
		WALK_SPEED) / TILE_SIZE][(int)(recup->p.py) / TILE_SIZE] == '0')
			recup->p.px += cos(recup->p.ang) * WALK_SPEED;
		if (recup->map[(int)(recup->p.px) / TILE_SIZE][(int)
		(recup->p.py + sin(recup->p.ang) * WALK_SPEED) / TILE_SIZE] == '0')
			recup->p.py += sin(recup->p.ang) * WALK_SPEED;
	}
	else if (recup->d.back == 1)
	{
		if (recup->map[(int)(recup->p.px - cos(recup->p.ang) *
		WALK_SPEED) / TILE_SIZE][(int)(recup->p.py - sin(recup->p.ang) *
		WALK_SPEED) / TILE_SIZE] == '0')
		{
			recup->p.px -= cos(recup->p.ang) * WALK_SPEED;
			recup->p.py -= sin(recup->p.ang) * WALK_SPEED;
		}
	}
}

void	ft_left_right(t_recup *recup)
{
	if (recup->d.left == 1)
	{
		if (recup->map[(int)(recup->p.px - cos(recup->p.ang + M_PI2) *
		WALK_SPEED) / TILE_SIZE][(int)(recup->p.py - sin(recup->p.ang + M_PI2)
		* WALK_SPEED) / TILE_SIZE] == '0')
		{
			recup->p.px -= cos(recup->p.ang + M_PI2) * WALK_SPEED;
			recup->p.py -= sin(recup->p.ang + M_PI2) * WALK_SPEED;
		}
	}
	else if (recup->d.right == 1)
	{
		if (recup->map[(int)(recup->p.px + cos(recup->p.ang + M_PI2)
		* WALK_SPEED) / TILE_SIZE][(int)(recup->p.py +
		sin(recup->p.ang + M_PI2) * WALK_SPEED) / TILE_SIZE] == '0')
		{
			recup->p.px += cos(recup->p.ang + M_PI2) * WALK_SPEED;
			recup->p.py += sin(recup->p.ang + M_PI2) * WALK_SPEED;
		}
	}
}

void	ft_rotate_right_left(t_recup *recup)
{
	recup->p.ang = ft_normalize_ang(recup->p.ang);
	if (recup->d.rotate_left == 1)
		recup->p.ang += ROT_SPEED;
	else if (recup->d.rotate_right == 1)
		recup->p.ang -= ROT_SPEED;
}
