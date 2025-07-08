/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 14:32:49 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3d_H
# define cub3d_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../src/get_next_line/get_next_line.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int	floor[3];
	int	ceiling[3];
}	t_colors;

typedef	struct s_cub3d
{
	t_textures	textures;
	t_colors	colors;
	char	**map;
}	t_cub3d;

// FUNCTIONS :

// str utils
char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_is_letter(char c);
int		skip_letter(char current, char next);
void	skip_spaces(char *str, int *i);
char	**ft_split(char *str, char c);
int		ft_atoi(char *str);
char	**ft_split(char *str, char c);
int		ft_tablen(char **tab);
int		ft_isdigit(char c);

char	*ft_strdup(char *s);

void	exit_error(char *err);

char	**open_file(char *filename);
int		check_extension(char *filename);
int		check_and_set_file(t_cub3d *cub3d, char **file);

int		get_max_width(char **map);
t_point	find_player_position(char **map, t_point size);
int		flood_fill(char **tab, t_point size, t_point begin);
t_point	find_player_position(char **map, t_point size);
int		check_no_space_adjacent(char **tab, t_point size);

void	init(t_cub3d *cub3d);
char	**map_cpy(char **old);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	free_map(char **map);

#endif