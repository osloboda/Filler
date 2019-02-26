/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 14:00:27 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/24 14:00:49 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

void			free_map_piece(t_figure *piece)
{
	int			i;

	i = 0;
	while (piece->map[i])
		ft_strdel(&piece->map[i++]);
	free(piece->map);
	piece->map = NULL;
}

int				ft_abs(int x)
{
	if (x < 0)
		return (x * -1);
	return (x);
}

void			check_b(t_figure *piece, int flag)
{
	int			x;
	int			y;

	y = piece->ma_y;
	while (y--)
	{
		x = piece->ma_x;
		while (x--)
		{
			if (flag && piece->map[y][x] == '*')
			{
				piece->bot[0] = y;
				piece->bot[1] = x;
				piece->right[0] = y;
				piece->right[1] = x;
				flag = 0;
			}
			else if (piece->map[y][x] == '*' && (x > piece->right[1]
					|| (x == piece->right[1] && y < piece->right[0])))
			{
				piece->right[0] = y;
				piece->right[1] = x;
			}
		}
	}
}

void			check_f(t_figure *piece, int flag)
{
	int			x;
	int			y;

	y = -1;
	while (++y < piece->ma_y)
	{
		x = -1;
		while (++x < piece->ma_x)
		{
			if (piece->map[y][x] == '*' && flag)
			{
				piece->top[0] = y;
				piece->top[1] = x;
				piece->left[0] = y;
				piece->left[1] = x;
				flag = 0;
			}
			else if (piece->map[y][x] == '*' && x < piece->left[1])
			{
				piece->left[0] = y;
				piece->left[1] = x;
			}
		}
	}
	check_b(piece, 1);
}

int				try_elem(t_map *map, t_figure *piece, int x, int y)
{
	int			xx;
	int			yy;

	yy = 0;
	while (yy < piece->ma_y)
	{
		xx = 0;
		while (xx < piece->ma_x)
		{
			if (piece->map[yy][xx] == '*')
			{
				if (x + xx < 1 || y + yy < 1 || y + yy >= map->ma_y
				|| x + xx >= map->ma_x || (map->map[y + yy][x + xx] != '.'
						&& (y + yy != map->curr[0] || x + xx != map->curr[1])))
					return (0);
			}
			xx++;
		}
		yy++;
	}
	return (1);
}
