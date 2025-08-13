/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/13 17:00:19 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "../minilibx-linux/mlx.h"

# include "../src/get_next_line/get_next_line.h"

# define PI 3.14159265358979323846264338327950288

typedef struct s_cub3d	t_cub3d;

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
	int		floor[3];
	int		ceiling[3];
	t_cub3d	*cub3d;
}	t_colors;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
}	t_mlx;

typedef struct s_player
{
	t_point		*coords;
	double		posX;
	double		posY;
	char		dir;
	float		dirX;
	float		dirY;
	int			fov;
}	t_player;

typedef struct s_view
{
	float	planeX;
	float	planeY;
}	t_view;

typedef struct s_dda
{
	double	map_x;
	double	map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_dda;

typedef struct s_cub3d
{
	t_mlx		mlx;
	t_textures	textures;
	t_colors	colors;
	t_player	player;
	t_view		view;
	char		**map;
	char		keys[256];
	char		alpha[26];
}	t_cub3d;

// FUNCTIONS :

// check textures
int		ft_check_textures(t_textures *textures, char **file, int *idx);

// check colors
int		ft_check_colors(t_colors *colors, char **file, int *idx);

// check map
int		ft_check_map(t_cub3d *cub3d, char **file, int *idx_line);

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
int		in_map(char c);
char	*ft_strndup(char *str, int n);
char	*ft_strdup(char *s);
int		only_numbers(char *str);
int		is_nbr(char *str);
void	ft_check_letter(t_cub3d *cub3d);
int		count_islands(t_cub3d *cub3d, char **work_map);

t_off	collen(char **map, int y, int x);
t_off	linelen(char **map, int y, int x);
void	print_map(t_cub3d *cub3d, char **map);

void	exit_error(char *err, t_cub3d *cub3d);

char	**open_file(t_cub3d *cub3d, char *filename);
int		check_extension(t_cub3d *cub3d, char *filename);
int		check_and_set_file(t_cub3d *cub3d, char **file);

t_point	find_player_position(t_cub3d *cub3d, char **map);
int		flood_fill(char ***tab, t_point current, char to_fill, char new);
int		flood_fill_z(char ***map, t_point here, char to_fill);
int		check_adjacent(int y, int x, char **map, char new);
t_point	*check_char_remaining(t_cub3d *cub3d, char **work_map, char c);

int		check_text_extension(t_cub3d *cub3d, char *textures);
int		all_text_set(t_textures textures);
int		all_colors_set(t_colors colors);
void	set_ceiling(t_colors *colors, char **split);
void	set_floor(t_colors *colors, char **split);

void	init(t_cub3d *cub3d);
char	**map_cpy(char **old);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	free_map(char **map);
t_cub3d	*init_mlx(t_cub3d *cub3d);


//draw
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//camera
void	calc_camera_plane(t_cub3d *cub3d);

//raycasting utils
void	init_dda_params(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y,
			t_dda *dda);
void	init_step_and_side_dist(t_dda *dda, double ray_dir_x,
			double ray_dir_y, t_cub3d *cub3d);
void	init_step_and_side_dist_y(t_dda *dda, double ray_dir_y,
			t_cub3d *cub3d);
void	perform_dda_algorithm(t_cub3d *cub3d, t_dda *dda);
double	calc_perpendicular_wall_distance(t_dda *dda, double ray_dir_x,
			double ray_dir_y, t_cub3d *cub3d);

//render
void	calc_line_bounds(double perp_wall_dist, int *draw_start, int *draw_end);
void	draw_wall_slice(t_cub3d *cub3d, int screen_x, double perp_wall_dist,
	int side);
void	draw_wall_pixels(t_cub3d *cub3d, int screen_x, int draw_start,
			int draw_end);
void	draw_floor_ceiling(t_cub3d *cub3d, int screen_x, int draw_start,
			int draw_end);

//raycasting
void	cast_single_ray(t_cub3d *cub3d, int screen_x);
void	raycast(t_cub3d *cub3d);

//hook
int		handle_close(t_cub3d *cub3d);
int		handle_hook(int keycode, t_cub3d *cub3d);
int		handle_movement(t_cub3d *cub3d);
int		handle_movement_strafe(t_cub3d *cub3d, double move_speed);
int		handle_direction(t_cub3d *cub3d);
int		handle_direction_left(t_cub3d *cub3d, double rot_speed);
int		handle_direction_right(t_cub3d *cub3d, double rot_speed);
int		handle_keypress(int keycode, t_cub3d *cub3d);
int		handle_keyrelease(int keycode, t_cub3d *cub3d);
int		handle_loop(t_cub3d *cub3d);
int		check_any_key_pressed(t_cub3d *cub3d);
void	refresh_image(t_cub3d *cub3d);

//collision
int		is_valid_position(t_cub3d *cub3d, double x, double y);
int		move_player(t_cub3d *cub3d, double delta_x, double delta_y);


#endif