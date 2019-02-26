/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:57:51 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/10 16:58:52 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "mlx.h"
# include "../libft/libft.h"
# include "limits.h"
# include <fcntl.h>

typedef struct	s_map
{
	char		**map;
	char		type;
	int			ma_x;
	int			ma_y;
	int			curr[2];
	int			distance[3];

}				t_map;

typedef struct	s_figure
{
	char		**map;
	int			ma_x;
	int			ma_y;
	int			curr[2];
	int			top[2];
	int			right[2];
	int			left[2];
	int			bot[2];
}				t_figure;

void			solver(t_map *map, t_figure *piece);
void			free_map_piece(t_figure *piece);
int				ft_abs(int x);
void			check_f(t_figure *piece, int flag);
int				try_elem(t_map *map, t_figure *piece, int x, int y);

#endif
