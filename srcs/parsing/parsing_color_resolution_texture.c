/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_color_resolution_texture.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:04:31 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 12:28:24 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int			ft_strlen2(char *str)
{
	int j;
	int i;

	j = 0;
	i = 0;
	while (str[i] != '.')
		i++;
	while (str[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

int			ft_path_texture(char *str, char **texture, t_recup *recup, int j)
{
	recup->count2 = 0;
	if (*texture != NULL)
	{
		recup->erreur = 2;
		return (0);
	}
	if (ft_charinstr(str, '.') == 0 || ft_charinstr(str, '/') == 0
			|| ft_strlen2(str) <= 2)
		recup->erreur = 2;
	while (str[j] != '.')
	{
		if (str[j] != ' ' && str[j] != '.')
			recup->erreur = 2;
		j++;
	}
	if (!(*texture = (char *)(malloc(sizeof(char) * (ft_strlen2(str) + 1)))))
		recup->erreur = 2;
	while (str[j] != '\0')
	{
		(*texture)[recup->count2] = str[j];
		recup->count2++;
		j++;
	}
	(*texture)[recup->count2] = '\0';
	return (0);
}

void		ft_texture(char *str, t_recup *recup)
{
	int			i;
	static int	j = 0;

	i = 0;
	if (str[i] == 'S' && str[i + 1] == 'O' && str[i + 2] == ' ')
		ft_path_texture(str, &recup->so, recup, 2);
	else if (str[i] == 'N' && str[i + 1] == 'O' && str[i + 2] == ' ')
		ft_path_texture(str, &recup->no, recup, 2);
	else if (str[i] == 'E' && str[i + 1] == 'A' && str[i + 2] == ' ')
		ft_path_texture(str, &recup->ea, recup, 2);
	else if (str[i] == 'W' && str[i + 1] == 'E' && str[i + 2] == ' ')
		ft_path_texture(str, &recup->we, recup, 2);
	else if (str[i] == 'S' && str[i + 1] == ' ')
		ft_path_texture(str, &recup->sp, recup, 1);
	else if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E'
			&& str[0] != 'R' && str[0] != 'F' && str[0] != 'C'
			&& str[0] > 65 && str[0] < 122)
		recup->erreur = 2;
	j++;
}

void		ft_get_color(char *str, t_recup *recup, int i)
{
	if (str[i] == 'F' && str[i + 1] == ' ')
		ft_get_color_f(&str[i + 2], recup, 0, 0);
	else if (str[i] == 'C' && str[i + 1] == ' ')
		ft_get_color_c(&str[i + 2], recup, 0, 0);
	else
		recup->erreur = 2;
}

void		ft_color_resolution(char **str, t_recup *recup)
{
	int			i;

	i = 0;
	recup->i = 1;
	if (*str[i] == 'R')
	{
		i++;
		if (recup->rx != 0 && recup->ry != 0)
			recup->erreur = 2;
		recup->rx = ft_atoi2(*str, recup);
		recup->ry = ft_atoi2(*str, recup);
		if (ft_atoi2(*str, recup) > 0 || recup->rx == 0 || recup->ry == 0)
			recup->erreur = 2;
	}
	else if (*str[i] == 'F' || *str[i] == 'C')
		ft_get_color(*str, recup, 0);
}
