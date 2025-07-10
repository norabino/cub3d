/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/10 22:20:08 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef cub3d_H
# define cub3d_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../src/get_next_line/get_next_line.h"

typedef	struct s_cub3d		t_cub3d;

typedef struct s_off
{
	int		offset;
	int		len;
}	t_off;

typedef struct s_point
{
	int		x;
	int		y;
	char	direction;
	t_cub3d	*cub3d;
}	t_point;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_cub3d	*cub3d;
}	t_textures;

typedef struct s_colors
{
	int	floor[3];
	int	ceiling[3];
	t_cub3d	*cub3d;
}	t_colors;

typedef	struct s_cub3d
{
	t_point		coords;
	t_textures	textures;
	t_colors	colors;
	char	**map;
	char	alpha[26];
}	t_cub3d;

// FUNCTIONS :

// str utils
char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		is_letter(char c);
int		skip_letter(char current, char next);
void	skip_spaces(char *str, int *i);
char	**ft_split(char *str, char c);
int		ft_atoi(char *str);
char	**ft_split(char *str, char c);
int		ft_tablen(char **tab);
int		ft_isdigit(char c);
char	*ft_strcpy(char *dest, char *str);

t_off	collen(char **map, int y, int x);
t_off	linelen(char **map, int y, int x);
void	print_map(t_cub3d *cub3d, char **map);

void	exit_error(char *err, t_cub3d *cub3d);

char	**open_file(t_cub3d *cub3d, char *filename);
int		check_extension(t_cub3d *cub3d, char *filename);
int		check_and_set_file(t_cub3d *cub3d, char **file);

int		ft_get_max_width(char **map);
t_point find_player_position(t_cub3d *cub3d, char **map);
int		flood_fill(char ***tab, t_point current, char to_fill, char new);
int		check_no_invalid_adjacent(char **tab);
t_point	*check_zero_remaining(t_cub3d *cub3d, char **work_map);


void	init(t_cub3d *cub3d);
char	**map_cpy(char **old);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	free_map(char **map);
char	*ft_strdup(char *s);

#endif