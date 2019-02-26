/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 15:18:04 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/11 15:18:29 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

int				dop_count_manhatan(t_map *map, t_figure *piece)
{
	if ((ft_abs(map->curr[1] - piece->right[1] + piece->left[1] -
	piece->curr[1]) + ft_abs(map->curr[0] - piece->right[0] + piece->left[0]
	- piece->curr[0])) < map->distance[0] && try_elem(map, piece,
			map->curr[1] - piece->right[1], map->curr[0] - piece->right[0]))
	{
		map->distance[0] = (ft_abs(map->curr[1] - piece->right[1] -
				piece->left[1] - piece->curr[1]) + ft_abs(map->curr[0] -
						piece->right[0] - piece->left[0] - piece->curr[0]));
		map->distance[1] = map->curr[1] - piece->right[1];
		map->distance[2] = map->curr[0] - piece->right[0];
	}
	if ((ft_abs(map->curr[1] + piece->top[1] - piece->bot[1] - piece->curr[1])
	+ ft_abs(map->curr[0] + piece->top[0] - piece->bot[0] - piece->curr[0]))
	< map->distance[0] && try_elem(map, piece, map->curr[1] - piece->bot[1],
			map->curr[0] - piece->bot[0]) && piece->ma_y > 1)
	{
		map->distance[0] = ((ft_abs(map->curr[1] + piece->top[1] -
				piece->bot[1] - piece->curr[1]) + ft_abs(map->curr[0] +
						piece->top[0] - piece->bot[0] - piece->curr[0])));
		map->distance[1] = map->curr[1] - piece->bot[1];
		map->distance[2] = map->curr[0] - piece->bot[0];
	}
	if (map->distance[0] == map->ma_x * map->ma_y)
		return (0);
	return (1);
}

int				count_manhatan(t_map *map, t_figure *piece)
{
	if ((ft_abs(map->curr[1] + piece->right[1] - piece->left[1] -
	piece->curr[1]) + ft_abs(map->curr[0] + piece->right[0] - piece->left[0]
	- piece->curr[0])) < map->distance[0] && try_elem(map, piece,
			map->curr[1] - piece->left[1], map->curr[0] - piece->left[0]))
	{
		map->distance[0] = (ft_abs(map->curr[1] + piece->right[1] -
				piece->left[1] - piece->curr[1]) + ft_abs(map->curr[0] +
						piece->right[0] - piece->left[0] - piece->curr[0]));
		map->distance[1] = map->curr[1] - piece->left[1];
		map->distance[2] = map->curr[0] - piece->left[0];
	}
	if ((ft_abs(map->curr[1] - piece->top[1] + piece->bot[1] - piece->curr[1])
	+ ft_abs(map->curr[0] - piece->top[0] + piece->bot[0] - piece->curr[0]))
	< map->distance[0] && try_elem(map, piece, map->curr[1] - piece->top[1],
			map->curr[0] - piece->top[0]))
	{
		map->distance[0] = ((ft_abs(map->curr[1] + piece->top[1] -
				piece->bot[1] - piece->curr[1]) + ft_abs(map->curr[0] +
						piece->top[0] - piece->bot[0] - piece->curr[0])));
		map->distance[1] = map->curr[1] - piece->top[1];
		map->distance[2] = map->curr[0] - piece->top[0];
	}
	return (dop_count_manhatan(map, piece));
}

int				cul_d(t_map *map, int x, int y, t_figure *piece)
{
	int			xx;
	int			yy;
	int			distance;

	yy = 0;
	distance = map->ma_y * map->ma_x;
	while (yy < map->ma_y)
	{
		xx = 0;
		while (xx < map->ma_x)
		{
			if (map->map[yy][xx] != '.' && map->map[yy][xx] != map->type &&
			map->map[yy][xx] != map->type + 32 &&
			(abs(x - xx) + abs(y - yy)) < distance)
			{
				distance = (abs(x - xx) + abs(y - yy));
				piece->curr[0] = yy;
				piece->curr[1] = xx;
			}
			xx++;
		}
		yy++;
	}
	return (distance);
}

void			check_distance(t_map *map, t_figure *piece)
{
	int			distance;
	int			x;
	int			y;
	int			tmp;

	y = 0;
	distance = map->ma_y + map->ma_x;
	while (y < map->ma_y)
	{
		x = 0;
		while (x < map->ma_x)
		{
			if (map->map[y][x] == map->type || map->map[y][x] == map->type + 32)
			{
				tmp = cul_d(map, x, y, piece);
				map->curr[0] = y;
				map->curr[1] = x;
				map->distance[0] = map->ma_x * map->ma_y;
				if (tmp < distance && count_manhatan(map, piece))
					distance = tmp;
			}
			x++;
		}
		y++;
	}
}

void			solver(t_map *map, t_figure *piece)
{
	check_f(piece, 1);
	map->distance[1] = 0;
	map->distance[2] = 0;
	check_distance(map, piece);
	ft_putnbr(map->distance[2]);
	ft_putchar(' ');
	ft_putnbr(map->distance[1]);
	ft_putchar('\n');
}
