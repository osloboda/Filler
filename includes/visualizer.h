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

# include "../libft/libft.h"
# include "limits.h"
# include "math.h"
# include <fcntl.h>
# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>

typedef struct		s_map
{
	TTF_Font		*font[2];
	SDL_Color		color[5];
	SDL_Rect		rect[6];
	SDL_Surface		*message[6];
	const Uint8		*keystate;
	char			**map;
	char			*p1;
	char			*p2;
	char			*score1;
	char			*score2;
	int				p1_score;
	int				p2_score;
	int				is_running;
	int				k;
	int				ma_x;
	int				ma_y;
	int				x_pad;
	int				win_x;
	int				win_y;
	int				col;
}					t_map;

void				clear_by_color(SDL_Surface *surface, unsigned int color);
void				win(t_map *map, SDL_Surface *surface, SDL_Window *window);
int					loop_key_hook(t_map *map,
		SDL_Surface *surface, SDL_Window *window);
int					render2d(SDL_Surface *surface, t_map *map);

#endif
