/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:19:22 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 16:17:14 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "variables.h"

typedef struct s_txt_i
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_txt_i;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_portal_sprite
{
	t_txt_i	*frames;
	char	**path;
	int		current_frame;
	int		frame_counter;
	long	last_frame_time;
}	t_prtl_sprite;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
	int		portal_index;
	char	portal_name;
}	t_sprite;

typedef struct s_sprite_calc
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
}	t_sprite_calc;

typedef struct s_sprite_render_data
{
	int		x;
	int		tex_x;
	int		current_frame;
	t_txt_i	*current_texture;
}	t_sprite_render_data;

typedef struct s_zbuffer
{
	double	*buffer;
	int		width;
}	t_zbuffer;

typedef struct s_portal
{
	char			name;
	t_point			p1;
	t_point			p2;
}	t_prtl;

typedef struct s_textures
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	char		*floor;
	char		*ceiling;
	char		*portals;
	t_txt_i		north_img;
	t_txt_i		south_img;
	t_txt_i		west_img;
	t_txt_i		east_img;
	t_txt_i		floor_img;
	t_txt_i		ceiling_img;
}	t_textures;

typedef struct s_colors
{
	int		floor[3];
	int		ceiling[3];
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
	double		pos_x;
	double		pos_y;
	char		dir;
	float		dir_x;
	float		dir_y;
	int			fov;
	char		direction;
	t_point		last_prtl_pos;
}	t_player;

typedef struct s_view
{
	float	plane_x;
	float	plane_y;
}	t_view;

typedef struct s_texture_calc
{
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	double	perp_wall_dist;
	t_txt_i	*current_text;
	int		is_portal;
	int		portal_index;
}	t_texture_calc;

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
	double	ray_dir_x;
	double	ray_dir_y;
}	t_dda;

typedef struct s_minimap_calc
{
	double	player_x;
	double	player_y;
	double	cos_angle;
	double	sin_angle;
}	t_minimap_calc;

typedef struct s_minimap_screen
{
	int	x;
	int	y;
}	t_minimap_screen;

typedef struct s_fc_coords
{
	double	floor_x;
	double	floor_y;
	int		screen_x;
	int		y;
}	t_fc_coords;

typedef struct s_minimap_render
{
	double	world_x;
	double	world_y;
	int		screen_x;
	int		screen_y;
}	t_minimap_render;

typedef struct s_triangle_draw
{
	int	center_x;
	int	center_y;
	int	y;
	int	half_width;
}	t_triangle_draw;

typedef struct s_pixel_draw
{
	int	x;
	int	y;
	int	center_x;
	int	center_y;
}	t_pixel_draw;

typedef struct s_time
{
	long	last_refresh;
	long	fps_last_time;
	int		fps_frame_count;
	double	current_fps;
	double	delta_time;
}	t_time;

typedef struct s_mouse
{
	int		x;
	int		y;
	int		last_x;
	int		captured;
}	t_mouse;

typedef struct s_cub3d
{
	char			**file;
	char			**map;
	t_mlx			mlx;
	t_player		player;
	t_colors		colors;
	t_textures		textures;
	t_time			time;
	t_view			view;
	t_mouse			mouse;
	t_prtl			*tp_portals;
	t_prtl_sprite	prtl_sprites;
	t_sprite		*sprites;
	t_zbuffer		zbuffer;
	int				sprite_count;
	int				portals[26];
	int				nb_portals;
	char			input_state[256];
	char			*invalid_arg;
	int				nb_error_line;
}	t_cub3d;

#endif