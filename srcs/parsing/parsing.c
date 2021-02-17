/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abettach <abettach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 17:04:26 by abettach          #+#    #+#             */
/*   Updated: 2020/12/10 11:24:52 by abettach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub.h"

int		ft_check_number(t_recup *recup, char *str)
{
	int i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] >= '0' && str[i] <= '9')
	{
		while (str[i] >= '0' && str[i] <= '9')
			i++;
		if (str[i] == ' ')
			while (str[i] == ' ')
				i++;
		if (str[i] == ',' || str[i] == '\0')
			return (1);
		else
			ft_error(recup, "Error\nMauvaises donnees C || F\n");
	}
	else
		ft_error(recup, "Error\nMauvaises donnees C || F\n");
	return (0);
}

int		ft_parsing_map(char *fichier, t_recup *recup)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	fd = open(fichier, O_RDONLY);
	if (!(recup->map = malloc(sizeof(char *) * recup->nblines)))
		return (0);
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, recup);
		if (recup->insidemap == 1 && ft_lignevide(str) == 0 &&
			recup->count < recup->nblines)
			recup->lignevide = 1;
		if ((recup->insidemap = ft_is_map(str, recup)) == 1)
			ft_copy_map(str, recup);
		free(str);
	}
	close(fd);
	ft_init_sprite(recup);
	return (0);
}

void	ft_parsing(char *fichier, t_recup *recup)
{
	int		fd;
	int		ret;
	char	*str;

	ret = 1;
	str = NULL;
	if ((fd = open(fichier, O_RDONLY)) == -1)
		ft_error(recup, "Error\nFichier .cub invalide\n");
	recup->erreur = 0;
	while (ret != 0)
	{
		ret = get_next_line(fd, &str, recup);
		if (recup->erreur == 2 || (ft_is_map(str, recup) != 1 && str[0] == ' ')
		|| (recup->nblines > 0 && recup->sizeline > 0 &&
		ft_is_map(str, recup) != 1))
			ft_error(recup, "Error\nLa partie parsing detecte une erreur\n");
		ft_color_resolution(&str, recup);
		ft_texture(str, recup);
		ft_map(str, recup);
		free(str);
	}
	close(fd);
	if (recup->sizeline == 0 || recup->nblines == 0)
		ft_error(recup, "Error\nMap absente\n");
	ft_parsing_map(fichier, recup);
}

int		ft_cub(char *str, t_recup *recup)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (str[i] != '.')
		i--;
	if (i == 0)
		ft_error(recup, "Error\nNom Du map invalide\n");
	if (str[i] == '.' && str[i + 1] == 'c' && str[i + 2] == 'u' &&
	str[i + 3] == 'b' && !str[i + 4])
		ft_parsing(str, recup);
	else
		ft_error(recup, "Error\nNom Du map invalide\n");
	return (0);
}

int		main(int argc, char **argv)
{
	t_recup recup;

	ft_initialisation(&recup);
	if (argc == 1)
		ft_error(&recup, ".cub file note found !!\n");
	if (argc == 2 || (argc == 3 && ft_check_save(argv[2]) == 1))
	{
		if (argc == 3)
			recup.save = 1;
		ft_cub(argv[1], &recup);
	}
	else
		ft_error(&recup, "La partie parssing detecte un erreur\n");
	return (0);
}
