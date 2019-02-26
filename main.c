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

void drawText
        (SDL_Surface* screen, char* string,
         int size, int x, int y,
         int fR, int fG, int fB,
         int bR, int bG, int bB)
{

    TTF_Font* font = TTF_OpenFont("arial.ttf", size);

    SDL_Color foregroundColor = { fR, fG, fB, fB};
    SDL_Color backgroundColor = { bR, bG, bB, bB};

    SDL_Surface* textSurface
            = TTF_RenderText_Shaded
                    (font, string, foregroundColor, backgroundColor);

    SDL_Rect textLocation = { x, y, 0, 0 };

    SDL_BlitSurface(textSurface, NULL, screen, &textLocation);

    SDL_FreeSurface(textSurface);

    TTF_CloseFont(font);
}

int		render2d(SDL_Surface *surface, t_map *map)
{
	char 	*line;
	int 	y;
	int 	x;
	int     i;
	int     j;
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
				map->col = 0x434560;
			else if (line[x + 4] == 'O' || line[x + 4] == 'o')
				map->col = 0xB5EE70;
			else
				map->col = 0x1A93B0;
			pixel[((x) * (int) map->k) + ((y * (int) map->k) * map->win_x + 100) + map->win_x * 100] = map->col;
			i = 0;
			while (i < map->k - 3)
            {
			    j = 0;
			    while (j < map->k - 3)
                {
                    pixel[((x) * (int) map->k + j) + ((y * (int) map->k) * map->win_x + map->win_x * i + 100) + map->win_x * 100] = map->col;
                    j++;
                }
			    i++;
            }
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
    SDL_Surface *pla1;
    pla1 = SDL_GetWindowSurface(window);
  //  SDL_Renderer* Main_Renderer = NULL;
 //   Main_Renderer = SDL_CreateRenderer(window, -1, 0);
   // TTF_Init();
//    TTF_Font* Sans = TTF_OpenFont("arial.ttf", 25);
//    SDL_Color White = {255, 255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
//    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, map->p1, White);
   // TTF_Quit();
//    SDL_Texture* Message = SDL_CreateTextureFromSurface(Main_Renderer, surfaceMessage); //now you can convert it into a texture
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect
//
//    SDL_RenderCopy(Main_Renderer, Message, NULL, &Message_rect);
//    SDL_RenderPresent(Main_Renderer);
//    SDL_SetRenderDrawColor(Main_Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
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
				    map->k = 50;
                else if (map->ma_y == 100)
                    map->k = 8;

			}
		}
		if (!ft_strncmp(line, "Plateau ", 8))
		{
			ft_strdel(&line);
			get_next_line(0, &line);
			render2d(surface, map);
            drawText(pla1, map->p1, 24, 0, 0, 255, 255, 255, 0, 0, 255);
            SDL_BlitSurface(surface, &Message_rect, pla1, NULL);
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
	clear_by_color(surface, 0x362865);
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
