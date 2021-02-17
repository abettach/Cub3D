/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:04:05 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 11:22:53 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_mf(t_recup *recup)
{
	int i;
	int j;

	i = -1;
	while (++i < recup->nblines)
	{
		j = -1;
		while (++j < recup->sizeline)
			if (recup->map[i][j] == ' ')
				recup->map[i][j] = '1';
	}
	i = 0;
	while (i < recup->nblines)
	{
		if (recup->map[i][0] != '1')
			return (1);
		i++;
	}
	return (0);
}

void	ft_error(t_recup *recup, char *str)
{
	int i;

	i = -1;
	write(1, str, ft_strlen(str));
	if (recup->no)
		free(recup->no);
	if (recup->so)
		free(recup->so);
	if (recup->we)
		free(recup->we);
	if (recup->ea)
		free(recup->ea);
	if (recup->sp)
		free(recup->sp);
	if (recup->map)
		while (++i < recup->nblines)
			free(recup->map[i]);
	if (recup->map)
		free(recup->map);
	exit(0);
}

void	ft_error3(t_recup *recup)
{
	if (recup->sxy)
		free(recup->sxy);
	if (recup->s.dist)
		free(recup->s.dist);
	if (recup->s.ang)
		free(recup->s.ang);
	if (recup->s.h)
		free(recup->s.h);
	if (recup->s.w)
		free(recup->s.w);
	if (recup->sdist)
		free(recup->sdist);
	exit(0);
}

void	ft_error2(t_recup *recup, char *str)
{
	int i;

	i = -1;
	write(1, str, ft_strlen(str));
	if (recup->no)
		free(recup->no);
	if (recup->so)
		free(recup->so);
	if (recup->we)
		free(recup->we);
	if (recup->ea)
		free(recup->ea);
	if (recup->sp)
		free(recup->sp);
	if (recup->map)
		while (++i < recup->nblines)
			free(recup->map[i]);
	if (recup->map)
		free(recup->map);
	ft_error3(recup);
}

void	ft_verify_errors(t_recup *recup)
{
	if (ft_murs(recup) == 1)
		ft_error(recup, "Error\nMap non entouree de 1\n");
	if (recup->depart == 'x')
		ft_error(recup, "Error\nPas de joueur\n");
	if (recup->multijoueurs == 1)
		ft_error(recup, "Error\nPlus d'un joueur\n");
	if (recup->wrongcharmap == 2)
		ft_error(recup, "Error\nCaractere incorrect dans la map\n");
	if (recup->lignevide == 1)
		ft_error(recup, "Error\nLigne vide dans la map\n");
}
