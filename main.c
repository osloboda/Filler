#include "includes/visualizer.h"
# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# include <SDL.h>			// Main header
# include <SDL_image.h>		// Image import/load
# include <SDL_ttf.h>		// Fonts live here

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

int		render2d(SDL_Surface *surface, t_map *map)
{
	char 	*line;
	int 	y;
	int 	x;
	unsigned int	*pixel;

	y = -1;
	map->x_pad = 100;
	map->y_pad = 100;
	pixel = surface->pixels;
	while (++y < map->ma_y && get_next_line(0, &line))
	{
		x = -1;
		while (++x < map->ma_x)
		{
			if (line[x + 4] == '.')
				map->col = 0xFFFFFF;
			else if (line[x + 4] == 'O' || line[x + 4] == 'o')
				map->col = 0xFF0000;
			else
				map->col = 0x0000FF;
			pixel[((x) * (int) map->k) + (((y + 100) * (int) map->k) * map->win_x + 100)]= map->col;
		//	pixel[(x * (int) map->k) + ((y * (int) map->k) * (int) map->k * map->win_x) + 1] = map->col;
		//	pixel[(x * (int) map->k) + ((y * (int) map->k) * (int) map->k * map->win_x) + 2] = map->col;
		//	pixel[(x * (int) map->k) + ((y * (int) map->k) * (int) map->k * map->win_x) + 3] = map->col;
		//	pixel[(x * (int) map->k) + ((y * (int) map->k) * (int) map->k * map->win_x) + 1] = map->col;
		}
		free(line);
	}
	return (0);
}

int			loop_key_hook(t_map *map, SDL_Surface *surface, SDL_Window *window)
{
	char	*line;
	char	*tmp;
	SDL_Event		event;
	const Uint8		*keystate;

	keystate = SDL_GetKeyboardState(NULL);
	while (get_next_line(0, &line))
	{
		if (*line == '$')
		{
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
                map->k = 25;
                if (map->ma_y == 15)
				    map->k = 45;
                else
                    map->k = 8;
			}
		}
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			render2d(surface, map);
			SDL_UpdateWindowSurface(window);
			if (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE])
					break ;
				loop_key_hook(map, surface, window);
			}
			SDL_Delay(5);
		}
		ft_strdel(&line);
	}
	return (0);
}

int					main(void)
{
	SDL_Window		*window;
	SDL_Surface		*surface;
	SDL_Event		event;
	const Uint8		*keystate;
	int				is_running;
	t_map	*map;

	map = malloc(sizeof(t_map));
	map->win_x = 1400;
	map->win_y = 1000;
	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, map->win_x, map->win_y, 0);
	surface = SDL_GetWindowSurface(window);
	keystate = SDL_GetKeyboardState(NULL);

	is_running = 1;
	clear_by_color(surface, 0x000000);
	SDL_UpdateWindowSurface(window);
	while (is_running)
	{
		// SDL_Delay(10);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE])
				is_running = 0;
			loop_key_hook(map, surface, window);
		}

	}
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
