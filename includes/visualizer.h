/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 15:38:16 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/24 15:40:01 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include "mlx.h"
# include "../libft/libft.h"
# include "limits.h"
# include "math.h"
# include <fcntl.h>

typedef struct	s_map
{
	char		**map;
	char 		*p1;
	char 		*p2;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	int 		*data;
	int			size_l;
	int			bpp;
	int			endian;
	double		k;
	int 		ma_x;
	int 		ma_y;
	double		high_save;
	double		high;
	int			y_s;
	int			x_s;
	int			y_pad;
	int			x_pad;
	int			x_mouse;
	int			y_mouse;
	int			press;
	int			iso;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			win_x;
	int			win_y;
	int			col;
	int			col_switch;
}				t_map;

#endif
