/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:04:12 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 12:29:45 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_charinstr(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_atoi_check(t_recup *recup, const char *str)
{
	if ((str[recup->i] < '0' || str[recup->i] > '9') && str[recup->i] != ' '
	&& str[recup->i] != '\0')
		recup->erreur = 2;
	if (str[recup->i] == ' ' && recup->rx != 0)
	{
		while (str[recup->i] == ' ')
			recup->i++;
		str[recup->i] != '\0' ? recup->erreur = 2 : str[recup->i];
	}
}

int		ft_atoi2(const char *str, t_recup *recup)
{
	recup->sum2 = 0;
	if (str[1] != ' ' || ft_charinstr((char *)str, ',') == 1)
		recup->erreur = 2;
	while (str[recup->i] == ' ' || str[recup->i] == '\t')
		recup->i++;
	if (str[recup->i] == '-' || str[recup->i] == '+')
		recup->erreur = 2;
	while (str[recup->i] >= '0' && str[recup->i] <= '9')
	{
		if (recup->sum2 >= 21474636)
			break ;
		recup->sum2 = (recup->sum2 * 10) + (str[recup->i] - 48);
		recup->i++;
	}
	if (recup->sum2 >= 21474636)
	{
		recup->sum2 = 21474636;
		while (str[recup->i] >= '0' && str[recup->i] <= '9')
			recup->i++;
	}
	ft_atoi_check(recup, str);
	return (recup->sum2);
}

void	ft_get_color_f(char *str, t_recup *recup, int i, int j)
{
	int fcolor[3];

	if (ft_nb_virgule(str) != 2)
		ft_error(recup, "Error\nMauvaises donnees F\n");
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
	{
		ft_check_number(recup, str);
		fcolor[j] = ft_atoi(str);
		while (*str != ',')
			str++;
		ft_check_number(recup, str + 1);
		fcolor[++j] = ft_atoi(++str);
		while (*str != ',')
			str++;
		ft_check_number(recup, str + 1);
		fcolor[++j] = ft_atoi(++str);
	}
	else
		ft_error(recup, "Error\nMauvaises donnees F\n");
	if ((fcolor[0] > 255 || fcolor[0] < 0) || (fcolor[1] > 255 ||
	fcolor[1] < 0) || (fcolor[2] > 255 || fcolor[2] < 0))
		ft_error(recup, "Error\nMauvaises donnees F\n");
	recup->f = fcolor[0] * 65536 + fcolor[1] * 256 + fcolor[2];
}

void	ft_get_color_c(char *str, t_recup *recup, int i, int j)
{
	int fcolor[3];

	if (ft_nb_virgule(str) != 2)
		ft_error(recup, "Error\nMauvaises donnees C\n");
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
	{
		ft_check_number(recup, str);
		fcolor[j] = ft_atoi(str);
		while (*str != ',')
			str++;
		ft_check_number(recup, str + 1);
		fcolor[++j] = ft_atoi(++str);
		while (*str != ',')
			str++;
		ft_check_number(recup, str + 1);
		fcolor[++j] = ft_atoi(++str);
	}
	else
		ft_error(recup, "Error\nMauvaises donnees C\n");
	if ((fcolor[0] > 255 || fcolor[0] < 0) || (fcolor[1] > 255 ||
	fcolor[1] < 0) || (fcolor[2] > 255 || fcolor[2] < 0))
		ft_error(recup, "Error\nMauvaises donnees C\n");
	recup->c = (fcolor[0] * 65536) + (fcolor[1] * 256) + fcolor[2];
}
