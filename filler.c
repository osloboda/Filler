/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: osloboda <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:57:30 by osloboda          #+#    #+#             */
/*   Updated: 2019/02/10 17:00:45 by osloboda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/filler.h"

void			read_plateau(int fd, t_map *map, char *line)
{
	int			i;

	i = 0;
	map->ma_y = ft_atoi((ft_strchr(line, ' ') + 1));
	map->ma_x = ft_atoi((ft_strchr(ft_strchr(line, ' ') + 1, ' ') + 1));
	ft_strdel(&line);
	get_next_line(fd, &line);
	ft_strdel(&line);
	if (!map->map)
	{
		map->map = (char **)malloc(sizeof(char *) * (map->ma_y + 1));
		while (i < map->ma_y && get_next_line(fd, &line))
		{
			map->map[i++] = ft_strdup(ft_strchr(line, ' ') + 1);
			ft_strdel(&line);
		}
		map->map[i] = NULL;
	}
	else
		while (map->map[i] && get_next_line(fd, &line) > -1)
		{
			ft_strcpy(map->map[i++], ft_strchr(line, ' ') + 1);
			ft_strdel(&line);
		}
}

void			read_piece(int fd, t_figure *piece)
{
	int			i;
	char		*line;

	i = 0;
	while (i < piece->ma_y && get_next_line(fd, &line) > -1)
		piece->map[i++] = line;
	piece->map[i] = NULL;
}

void			read_map_piece(int fd, t_map *map, t_figure *piece)
{
	char		*line;
	int			i;

	i = 0;
	map->map = NULL;
	while (get_next_line(0, &line) > -1 && line)
	{
		if (!ft_strncmp(line, "Plateau ", 8))
			read_plateau(fd, map, line);
		else if (!ft_strncmp(line, "Piece ", 6))
		{
			piece->ma_y = ft_atoi((ft_strchr(line, ' ') + 1));
			piece->ma_x = ft_atoi((ft_strchr(ft_strchr(line, ' ')
					+ 1, ' ') + 1));
			ft_strdel(&line);
			piece->map = (char **)malloc(sizeof(char *) * (piece->ma_y + 1));
			read_piece(fd, piece);
			solver(map, piece);
			free_map_piece(piece);
		}
	}
	i = 0;
	while (map->map[i])
		ft_strdel(&map->map[i++]);
	free(map->map);
}

void			get_start_info(t_map *map, int fd)
{
	char		*line;

	get_next_line(fd, &line);
	if (line[10] == '1')
		map->type = 'O';
	else
		map->type = 'X';
	ft_strdel(&line);
}

int				main(void)
{
	t_map		*map;
	t_figure	*piece;

	map = (t_map *)malloc(sizeof(t_map));
	piece = (t_figure *)malloc(sizeof(t_figure));
	get_start_info(map, 0);
	read_map_piece(0, map, piece);
	return (0);
}
