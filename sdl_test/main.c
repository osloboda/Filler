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

int			loop_key_hook(t_map *map)
{
	char	*line;
	char	*tmp;

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
				map->image = mlx_new_image(map->mlx_ptr, map->ma_x * (int)map->k, map->ma_y * (int)map->k);
				map->data = (int *)mlx_get_data_addr(map->image, &map->bpp, &map->size_l, &map->endian);
			}
		}
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			render2d(map);
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

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow("Filler", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT, 0);
	surface = SDL_GetWindowSurface(window);
	keystate = SDL_GetKeyboardState(NULL);

	is_running = 1;
	clear_by_color(surface, 0x99cc00);
	SDL_UpdateWindowSurface(window);
	while (is_running)
	{
		// SDL_Delay(10);
		if (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || keystate[SDL_SCANCODE_ESCAPE])
				is_running = 0;
			loop_key_hook(map);
		}

	}
	SDL_FreeSurface(surface);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return (0);
}
