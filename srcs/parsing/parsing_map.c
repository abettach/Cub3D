/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:04:38 by abettach          #+#    #+#             */
/*   Updated: 2020/12/09 14:21:47 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub.h"

int		ft_check_cols(t_recup *m)
{
	int		i;
	int		j;
	char	**s;

	s = m->map;
	j = -1;
	while (++j < m->sizeline)
	{
		i = 0;
		while (i < m->nblines - 1)
		{
			while (i < m->nblines - 1 && (j >= (int)ft_strlen(s[i])
			|| s[i][j] == ' '))
				i++;
			if (i < m->nblines - 1 && s[i][j] != '1')
				return (-1);
			while (i < m->nblines - 1 && (j < (int)ft_strlen(s[i])
			&& s[i][j] != ' '))
				i++;
			if (j < (int)ft_strlen(s[i - 1]) && s[i][j] == ' '
			&& s[i - 1][j] != '1' && s[i - 1][j] != ' ')
				return (-1);
		}
	}
	return (0);
}

int		ft_check_rows(t_recup *m)
{
	int		i;
	int		j;
	char	**s;

	s = m->map;
	i = -1;
	while (++i < m->nblines)
	{
		j = 0;
		while (s[i][j] != '\0')
		{
			while (s[i][j] == ' ')
				j++;
			if (s[i][j] && s[i][j] != '1')
				return (-1);
			while (s[i][j] && s[i][j] != ' ')
				j++;
			if (s[i][j] == '\0')
				break ;
			if (s[i][j - 1] != '1' && s[i][j - 1] != ' ')
				return (-1);
		}
	}
	return (ft_mf(m));
}

int		ft_copy_map(char *str, t_recup *recup)
{
	static int	i = 0;
	int			j;

	j = 0;
	if (!(recup->map[i] = (char *)malloc(sizeof(char) * recup->sizeline + 1)))
		return (0);
	while (j < ft_strlen(str))
	{
		if (ft_depart(str[j], recup, i, j) == 1)
			recup->map[i][j] = '0';
		else
			recup->map[i][j] = str[j];
		j++;
	}
	j--;
	while (++j < recup->sizeline)
		recup->map[i][j] = ' ';
	recup->map[i][j] = '\0';
	i++;
	return (0);
}

int		ft_is_map(char *str, t_recup *recup)
{
	int i;

	i = -1;
	if (!str)
		return (0);
	if (ft_charinstr(str, '1') == 1 || ft_charinstr(str, '0') == 1)
	{
		while (str[++i] != '\0')
			if (str[i] != ' ' && str[i] != '0' && str[i] != '1' \
					&& str[i] != '2' && str[i] != 'N' && str[i] != 'S' \
					&& str[i] != 'E' && str[i] != 'W' && str[i] != '\n'
					&& str[i] != '\t')
			{
				if (recup->insidemap == 1)
					recup->wrongcharmap = 2;
				return (0);
			}
		return (1);
	}
	return (0);
}

void	ft_map(char *str, t_recup *recup)
{
	int			i;
	static int	snblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(str, recup) == 1)
	{
		if (recup->f == -1 || recup->c == -1 || recup->no == NULL ||
				recup->so == NULL || recup->we == NULL ||
				recup->ea == NULL)
			recup->erreur = 2;
		if ((i = ft_strlen(str)) > ssizeline)
			ssizeline = i;
		++snblines;
	}
	recup->nblines = snblines;
	recup->sizeline = ssizeline;
}
