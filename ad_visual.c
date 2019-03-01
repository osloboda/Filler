/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ad_visual.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:08:57 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/01 13:10:36 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/visualizer.h"

void				win(t_map *map, SDL_Surface *surface, SDL_Window *window)
{
	char			*winner;

	if (map->p1_score >= map->p2_score)
		winner = ft_strjoin(map->p1, " win!");
	else
		winner = ft_strjoin(map->p2, " win!");
	if ((map->message[5] = TTF_RenderText_Solid(map->font[1],
												winner, map->color[4])))
	{
		map->rect[5].x = 400;
		map->rect[5].y = map->win_y / 2 - 50;
		SDL_BlitSurface(map->message[5], NULL, surface, &map->rect[5]);
		SDL_UpdateWindowSurface(window);
		free(winner);
	}
	SDL_FreeSurface(map->message[0]);
	SDL_FreeSurface(map->message[1]);
	SDL_FreeSurface(map->message[5]);
	SDL_FreeSurface(map->message[4]);
}

void				clear_by_color(SDL_Surface *surface, unsigned int color)
{
	unsigned int	*pixel;
	size_t			counter;

	if (surface->pixels)
	{
		pixel = surface->pixels;
		counter = surface->w * surface->h;
		while (counter--)
			*pixel++ = color;
	}
}
