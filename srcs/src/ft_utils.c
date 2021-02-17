/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 13:17:43 by abettach          #+#    #+#             */
/*   Updated: 2020/12/06 17:12:21 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_exit(t_recup *recup)
{
	if (recup->save == 1)
		ft_error2(recup, "--save. Done\n");
	else
		ft_error2(recup, "Good By\n");
	if (recup->d.img)
		mlx_destroy_image(recup->d.mlx_ptr, recup->d.img);
	if (recup->d.mlx_win)
		mlx_destroy_window(recup->d.mlx_ptr, recup->d.mlx_win);
	exit(0);
}

double	ft_normalize_ang(double ang)
{
	ang = remainder(ang, (2 * M_PI));
	if (ang < 0)
		ang = (2 * M_PI) + ang;
	return (ang);
}

void	ft_swap(t_recup *recup)
{
	double tmp;

	tmp = recup->rx;
	recup->rx = recup->ry;
	recup->ry = tmp;
	recup->rx = recup->rx > 1440 ? 1440 : recup->rx;
	recup->ry = recup->ry > 2560 ? 2560 : recup->ry;
}

void	ft_player_look(t_recup *recup, double ang)
{
	recup->p.facingup = ang > M_PI2 && ang < M_PI3;
	recup->p.facingdown = !recup->p.facingup;
	recup->p.facingright = ang > 0 && ang < M_PI;
	recup->p.facingleft = !recup->p.facingright;
}

char	haswallat(t_recup *recup, double x, double y)
{
	if (recup->map[(int)x / 64] && recup->map[(int)x / 64][(int)y / 64] != '1'
	&& recup->map[(int)x / 64][(int)y / 64] != '2')
		return (recup->map[(int)x / 64][(int)y / 64]);
	if (recup->map[(int)x / 64][(int)y / 64] == '2')
		return ('2');
	return ('1');
}
