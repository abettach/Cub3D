/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:04:43 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 11:21:24 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_lignevide(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '\t' && str[i] != ' ' && str[i] != '\0' &&
				str[i] != '\n' && str[i] != '\r' && str[i] != '\v'
				&& str[i] != '\f')
			return (1);
		i++;
	}
	return (0);
}

void	ft_init_sprite2(t_recup *recup, int i, int j, int k)
{
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
			if (recup->map[i][j] == '2')
			{
				recup->sxy[k].x = (double)i * 64 + 32;
				recup->sxy[k].y = (double)j * 64 + 32;
				k++;
			}
	}
	ft_swap(recup);
	if (!(recup->sdist = (double *)malloc(sizeof(double) * recup->ry)))
		ft_error2(recup, "Error\nsdist malloc probleme");
	ft_mlx(recup);
}

void	ft_init_sprite(t_recup *recup)
{
	int i;
	int j;

	i = -1;
	recup->s.nbspr = 0;
	ft_verify_errors(recup);
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
			if (recup->map[i][j] == '2')
				recup->s.nbspr++;
	}
	if (!(recup->sxy = (t_sprxy *)malloc(sizeof(t_sprxy) * recup->s.nbspr)))
		ft_error(recup, "Error\nMalloc sxy*");
	if (!(recup->s.dist = (double *)malloc(sizeof(double) * recup->s.nbspr)))
		ft_error2(recup, "Error\nMalloc s.dist*");
	if (!(recup->s.ang = (double *)malloc(sizeof(double) * recup->s.nbspr)))
		ft_error2(recup, "Error\nMalloc s.dist*");
	if (!(recup->s.h = (double *)malloc(sizeof(double) * recup->s.nbspr)))
		ft_error2(recup, "Error\nMalloc s.dist*");
	if (!(recup->s.w = (double *)malloc(sizeof(double) * recup->s.nbspr)))
		ft_error2(recup, "Error\nMalloc s.dist*");
	ft_init_sprite2(recup, -1, 0, 0);
}

int		ft_depart(char c, t_recup *recup, int i, int j)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (recup->depart != 'x')
			recup->multijoueurs = 1;
		recup->depart = c;
		recup->dx = i;
		recup->dy = j;
		return (1);
	}
	return (0);
}

int		ft_murs(t_recup *recup)
{
	int i;
	int j;

	i = ft_check_cols(recup);
	j = ft_check_rows(recup);
	if (ft_murs_util(recup->map[0]) == 1)
		ft_error(recup, "Error\nMap non entouree de 1\n");
	if (ft_murs_util(recup->map[recup->nblines - 1]) == 1)
		ft_error(recup, "Error\nMap non entouree de 1\n");
	if (i == -1 || j == -1)
		return (1);
	return (0);
}
