/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 19:22:49 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/28 19:22:58 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/visualizer.h"

void				dopr_2(SDL_Surface *surface, t_map *map, int y, char *line)
{
	int				i;
	int				j;
	int				x;
	unsigned int	*pixel;

	x = -1;
	pixel = surface->pixels;
	while (++x < map->ma_x)
	{
		if (line[x + 4] == '.')
			map->col = 0x434560;
		else if ((line[x + 4] == 'O' || line[x + 4] == 'o') && ++map->p1_score)
			map->col = 0xB5EE70;
		else if (map->p2_score++)
			map->col = 0x1A93B0;
		pixel[((x) * map->k) + ((y * (map->k) * map->win_x + 100) +
		map->win_x * 100) + map->x_pad] = map->col;
		i = -1;
		while (++i < map->k - 3 && (j = -1))
			while (++j < map->k - 3)
				pixel[((x) * map->k + j) + ((y * map->k) * map->win_x + map->
				win_x * i + 100) + map->win_x * 100 + map->x_pad] = map->col;
	}
	free(line);
}

int					render2d(SDL_Surface *surface, t_map *map)
{
	char			*line;
	int				y;

	y = -1;
	map->p1_score = 0;
	map->p2_score = 0;
	while (++y < map->ma_y && get_next_line(0, &line))
		dopr_2(surface, map, y, line);
	map->score1 = ft_itoa(map->p1_score);
	map->score2 = ft_itoa(map->p2_score);
	return (0);
}

void				colour_init(t_map *map)
{
	map->color[0].r = 181;
	map->color[0].g = 238;
	map->color[0].b = 112;
	map->color[0].a = 1;
	map->color[1].r = 26;
	map->color[1].g = 147;
	map->color[1].b = 176;
	map->color[1].a = 1;
	map->color[2].r = 26;
	map->color[2].g = 147;
	map->color[2].b = 176;
	map->color[2].a = 1;
	map->color[3].r = 255;
	map->color[3].g = 198;
	map->color[3].b = 94;
	map->color[3].a = 1;
	map->color[4].r = 121;
	map->color[4].g = 0;
	map->color[4].b = 94;
	map->color[4].a = 1;
}

void				m_init(t_map *map, SDL_Window *window, SDL_Surface *surface)
{
	SDL_Event	event;

	if ((map->font[0] = TTF_OpenFont("OpenSans-Regular.ttf", 32)) &&
		(map->font[1] = TTF_OpenFont("OpenSans-ExtraBold.ttf", 50)))
	{
		map->keystate = NULL;
		colour_init(map);
		window = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED, map->win_x, map->win_y, 0);
		surface = SDL_GetWindowSurface(window);
		map->keystate = SDL_GetKeyboardState(NULL);
		map->is_running = 1;
		clear_by_color(surface, 0x362865);
		SDL_UpdateWindowSurface(window);
		loop_key_hook(map, surface, window);
		while (map->is_running)
		{
			if (SDL_PollEvent(&event))
				if (event.type == SDL_QUIT ||
				map->keystate[SDL_SCANCODE_ESCAPE])
					map->is_running = 0;
		}
	}
}

int					main(void)
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	t_map			*map;

	map = malloc(sizeof(t_map));
	map->win_x = 1400;
	map->win_y = 1000;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	surface = NULL;
	window = NULL;
	m_init(map, window, surface);
	free(map->p1);
	TTF_CloseFont(map->font[0]);
	TTF_CloseFont(map->font[1]);
	free(map->p2);
	free(map);
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return (0);
}
