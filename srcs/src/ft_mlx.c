/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 18:26:19 by abettach          #+#    #+#             */
/*   Updated: 2020/12/09 12:55:23 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

void	ft_get_texture_adress(t_recup *recup)
{
	recup->texture[0].addr = (int *)mlx_get_data_addr(recup->texture[0].img,
			&recup->texture[0].bits_per_pixel,
			&recup->texture[0].line_length, &recup->texture[0].endian);
	recup->texture[1].addr = (int *)mlx_get_data_addr(recup->texture[1].img,
			&recup->texture[1].bits_per_pixel,
			&recup->texture[1].line_length, &recup->texture[1].endian);
	recup->texture[2].addr = (int *)mlx_get_data_addr(recup->texture[2].img,
			&recup->texture[2].bits_per_pixel,
			&recup->texture[2].line_length, &recup->texture[2].endian);
	recup->texture[3].addr = (int *)mlx_get_data_addr(recup->texture[3].img,
			&recup->texture[3].bits_per_pixel,
			&recup->texture[3].line_length, &recup->texture[3].endian);
	recup->texture[4].addr = (int *)mlx_get_data_addr(recup->texture[4].img,
			&recup->texture[4].bits_per_pixel,
			&recup->texture[4].line_length, &recup->texture[4].endian);
}

void	ft_get_texture(t_recup *recup)
{
	if (!(recup->texture[0].img = mlx_xpm_file_to_image(recup->d.mlx_ptr,
					recup->no, &(recup->texture[0].width),
					&(recup->texture[0].height))))
		ft_error2(recup, "Error\nTexture NO\n");
	if (!(recup->texture[1].img = mlx_xpm_file_to_image(recup->d.mlx_ptr,
					recup->so, &(recup->texture[1].width),
					&(recup->texture[1].height))))
		ft_error2(recup, "Error\nTexture SO\n");
	if (!(recup->texture[2].img = mlx_xpm_file_to_image(recup->d.mlx_ptr,
					recup->we, &(recup->texture[2].width),
					&(recup->texture[2].height))))
		ft_error2(recup, "Error\nTexture WE\n");
	if (!(recup->texture[3].img = mlx_xpm_file_to_image(recup->d.mlx_ptr,
					recup->ea, &(recup->texture[3].width),
					&(recup->texture[3].height))))
		ft_error2(recup, "Error\nTexture EA\n");
	if (!(recup->texture[4].img = mlx_xpm_file_to_image(recup->d.mlx_ptr,
					recup->sp, &(recup->texture[4].width),
					&(recup->texture[4].height))))
		ft_error2(recup, "Error\nTexture S\n");
	ft_get_texture_adress(recup);
}

int		ft_raycasting(t_recup *recup)
{
	ft_draw_floor_sky(recup);
	ft_render3dwalls(recup);
	if (recup->save == 1)
		ft_save(recup);
	mlx_put_image_to_window(recup->d.mlx_ptr, recup->d.mlx_win,
	recup->d.img, 0, 0);
	ft_forward_back(recup);
	ft_left_right(recup);
	ft_rotate_right_left(recup);
	return (0);
}

int		ft_mlx(t_recup *recup)
{
	recup->d.mlx_ptr = mlx_init();
	ft_get_texture(recup);
	recup->d.img = mlx_new_image(recup->d.mlx_ptr, recup->ry, recup->rx);
	recup->d.addr = (int *)mlx_get_data_addr(recup->d.img,
	&recup->d.bits_per_pixel, &recup->d.line_length, &recup->d.endian);
	ft_init(recup);
	if (recup->save == 1)
		ft_raycasting(recup);
	recup->d.mlx_win = mlx_new_window(recup->d.mlx_ptr,
	recup->ry, recup->rx, "cub3d");
	mlx_hook(recup->d.mlx_win, 17, 1L << 5, ft_exit, recup);
	mlx_hook(recup->d.mlx_win, 2, 1L << 0, ft_key_press, recup);
	mlx_loop_hook(recup->d.mlx_ptr, ft_raycasting, recup);
	mlx_hook(recup->d.mlx_win, 3, 1L << 1, ft_key_release, recup);
	mlx_loop(recup->d.mlx_ptr);
	return (0);
}
