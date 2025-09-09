/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:19:22 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/09 23:29:02 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

typedef struct s_texture_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture_img;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_portal_sprite
{
	t_texture_img	*frames;
	char			**path;
	int				current_frame;
	int				frame_counter;
	int				color_tint[3];
	long			last_frame_time;
}	t_prtl_sprite;

typedef struct s_portal
{
	char			name;
	t_point			p1;
	t_point			p2;
}	t_prtl;

typedef struct s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*floor;
	char			*ceiling;
	char			*portals;
	t_texture_img	north_img;
	t_texture_img	south_img;
	t_texture_img	west_img;
	t_texture_img	east_img;
	t_texture_img	floor_img;
	t_texture_img	ceiling_img;
	t_prtl_sprite	prtl_sprites;
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
	double			wall_x;
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	double			perp_wall_dist;
	t_texture_img	*current_text;
	int				is_portal;
	int				portal_index;
	int				portal_color[3];
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
	int				portals[26];
	int				nb_portals;
	char			input_state[256];
}	t_cub3d;