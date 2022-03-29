/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_int.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tconwy <tconwy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:32:17 by tconwy            #+#    #+#             */
/*   Updated: 2022/03/29 13:15:06 by tconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_f_c(t_zone *zone, char *colors, char id)
{
	t_rgb	rgb;
	char	**str;
	int		error;

	error = 0;
	while (*colors == ' ')
		colors++;
	str = ft_split(colors, ',');
	if (array_s((void **)str) != 3)
		error = 10;
	else
	{
		rgb = new_rgb(ft_atoi(str[0]), ft_atoi(str[1]), ft_atoi(str[2]));
		if (!color_valid_rgb(rgb))
			error = 10;
	}
	free_array((void **)str, ft_free);
	if (error)
		return (0);
	if (id == 'F')
		zone->floor = init_color(rgb);
	else
		zone->ceiling = init_color(rgb);
	return (1);
}

int	parse_identifier(t_zone *zone)
{
	int	valid;

	valid = -1;
	valid = pars_texture(zone->no, 0, zone);
	printf("\nasd1\n");
	valid = pars_texture(zone->so, 1, zone);
	printf("\nasd2\n");
	valid = pars_texture(zone->we, 2, zone);
	printf("\nasd3\n");
	valid = pars_texture(zone->ea, 3, zone);
	printf("\nasd4\n");
	valid = parse_f_c(zone, zone->f, 'F');
	printf("\nasd5\n");
	valid = parse_f_c(zone, zone->c, 'C');
	if (valid == -1)
		return (0);
	return (valid);
}

void	map_int_help(t_zone *zone)
{
	int	y;
	int	x;

	while (zone->matrice[y])
	{
		x = 0;
		zone->matr_int[y] = (int *)malloc(sizeof(int) * zone->width);
		while (zone->matrice[y][x])
		{
			if (zone->matrice[y][x] == '1')
				zone->matr_int[y][x] = 1;
			else if (zone->matrice[y][x] == ' ' || zone->matrice[y][x] == '0')
				zone->matr_int[y][x] = 0;
			else if (zone->matrice[y][x] == 'W')
			{
				zone->pos_y = y;
				printf("\n%d = y\n", y);
				zone->pos_x = x;
				zone->matr_int[y][x] = 3;
			}
			x++;
		}
		y++;
	}
}

void	map_int(t_zone *zone)
{
	zone->matr_int = (int **)malloc(sizeof(int *) * zone->height);
	map_int_help(zone);
	if (parse_identifier(zone) == 0)
		exit (1);
}
