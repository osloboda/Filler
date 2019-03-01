/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_visual.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:10:49 by osloboda          #+#    #+#             */
/*   Updated: 2019/03/01 13:11:15 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/visualizer.h"

void				plato_rend(t_map *map, char *line,
		SDL_Surface *surface, SDL_Window *window)
{
	get_next_line(0, &line);
	ft_strdel(&line);
	render2d(surface, map);
	if ((map->message[2] = TTF_RenderText_Solid(map->font[0],
												map->score1, map->color[0])))
	{
		map->rect[2].x = 1200;
		map->rect[2].y = 150;
	}
	if ((map->message[3] = TTF_RenderText_Solid(map->font[0],
												map->score2, map->color[1])))
	{
		map->rect[3].x = 1200;
		map->rect[3].y = 450;
	}
	SDL_FillRect(surface, &map->rect[4], 0x434560);
	SDL_BlitSurface(map->message[0], NULL, surface, &map->rect[0]);
	SDL_BlitSurface(map->message[1], NULL, surface, &map->rect[1]);
	SDL_BlitSurface(map->message[2], NULL, surface, &map->rect[2]);
	SDL_BlitSurface(map->message[3], NULL, surface, &map->rect[3]);
	SDL_UpdateWindowSurface(window);
	SDL_FreeSurface(map->message[2]);
	SDL_FreeSurface(map->message[3]);
	ft_strdel(&map->score1);
	ft_strdel(&map->score2);
}

void				first_rend2(t_map *map,
		SDL_Surface *surface, SDL_Window *window)
{
	if (map->message[0])
		SDL_FreeSurface(map->message[0]);
	if (map->message[1])
		SDL_FreeSurface(map->message[1]);
	if ((map->message[0] = TTF_RenderText_Solid(map->font[0],
												map->p1, map->color[0])))
	{
		map->rect[0].x = 1200;
		map->rect[0].y = 100;
	}
	if ((map->message[1] = TTF_RenderText_Solid(map->font[0],
												map->p2, map->color[1])))
	{
		map->rect[1].x = 1200;
		map->rect[1].y = 400;
	}
	if ((map->message[4] = TTF_RenderText_Solid(map->font[1],
												"Filler", map->color[0])))
	{
		map->rect[5].x = 500;
		map->rect[5].y = 10;
		SDL_BlitSurface(map->message[4], NULL, surface, &map->rect[5]);
	}
	SDL_UpdateWindowSurface(window);
}

char				*first_rend1(t_map *map, char *line,
		SDL_Surface *surface, SDL_Window *window)
{
	char			*tmp;

	tmp = ft_strchr(line, '/') + 1;
	while (ft_strchr(tmp, '/'))
		tmp = ft_strchr(tmp, '/') + 1;
	if (line[10] == '1')
		map->p1 = ft_strsub(tmp, 0, ft_strchr(tmp, '.') - tmp);
	else
	{
		map->p2 = ft_strsub(tmp, 0, ft_strchr(tmp, '.') - tmp);
		ft_strdel(&line);
		get_next_line(0, &line);
		map->ma_y = ft_atoi((ft_strchr(line, ' ') + 1));
		map->ma_x = ft_atoi((ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1));
		map->k = 23;
		if (map->ma_y == 15)
			map->k = 54;
		else if (map->ma_y == 100 && (map->x_pad = 70))
			map->k = 8;
		first_rend2(map, surface, window);
	}
	return (line);
}

void				inic(t_map *map)
{
	map->message[0] = NULL;
	map->message[1] = NULL;
	map->message[2] = NULL;
	map->message[3] = NULL;
	map->message[4] = NULL;
	map->message[5] = NULL;
	map->rect[4].x = 1140;
	map->rect[4].y = 0;
	map->rect[4].h = map->win_y;
	map->rect[4].w = map->win_x - 1140;
	map->x_pad = 0;
}

int					loop_key_hook(t_map *map,
		SDL_Surface *surface, SDL_Window *window)
{
	char			*line;
	SDL_Event		event;

	inic(map);
	while (map->is_running && get_next_line(0, &line))
	{
		SDL_Delay(3);
		if (*line == '$')
			line = first_rend1(map, line, surface, window);
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			ft_strdel(&line);
			plato_rend(map, line, surface, window);
		}
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || map->keystate[SDL_SCANCODE_ESCAPE])
				map->is_running = 0;
			ft_strdel(&line);
		}
		ft_strdel(&line);
	}
	win(map, surface, window);
	return (1);
}
