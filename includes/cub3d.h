/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/15 17:53:54 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <time.h>
# include <string.h>

# include "../MinilibX/mlx.h"
# include "../src/get_next_line/get_next_line.h"
# include "./struct.h"
# include "./variables.h"


// ============================================================================
// COLLISION FUNCTIONS
// ============================================================================

int		check_bottom_corners(t_cub3d *cub3d, double x, double y);
int		check_corner_positions(t_cub3d *cub3d, double x, double y);
int		is_valid_position(t_cub3d *cub3d, double x, double y);
int		move_player(t_cub3d *cub3d, double delta_x, double delta_y);

// ============================================================================
// ERROR AND UTILITY FUNCTIONS
// ============================================================================

void	exit_error(char *err, t_cub3d *cub3d);
void	ft_free(t_cub3d *s_cub3d);


// ============================================================================
// FILE PARSING FUNCTIONS
// ============================================================================

int		all_colors_set(t_cub3d *cub3d);
int		all_text_set(t_cub3d *cub3d);
int		check_and_set_file(t_cub3d *cub3d);
int		check_extension(t_cub3d *cub3d, char *filename, char *ext);
int		count_file_lines(int fd);
int		extract_filename_from_line(char *line, int j, char **filename);
int		validate_all_colors(t_cub3d *cub3d, int *idx);
int		ft_check_map(t_cub3d *cub3d, int *idx_line);
int		validate_all_textures(t_cub3d *cub3d, int *idx);
char	**open_file(t_cub3d *cub3d, char *filename);
int		parse_color_line(t_cub3d *cub3d, char *line, int *idx, int i);
int		process_single_texture_line(t_cub3d *cub3d, int i,
			int *found_all);
void	process_texture_path_found(t_cub3d *cub3d, int j, int z, int i);
void	process_texture_found(t_cub3d *cub3d, char *line, int j, int z);
void	read_file_lines(char **file, int fd);
void	set_ceiling(t_cub3d *cub3d, char **split);
void	set_floor(t_cub3d *cub3d, char **split);
void	set_texture(char c, int j, char *line, t_cub3d *cub3d);
void	assign_color_values(t_cub3d *cub3d, char **split, char c);
void	validate_colors_complete(t_cub3d *cub3d);
int		parse_texture_line(t_cub3d *cub3d, int i);
void	parse_config_file(t_cub3d *cub3d, int ac, char **av);
int		validate_config_file(t_cub3d *cub3d);

// ============================================================================
// FPS AND TIME FUNCTIONS
// ============================================================================

void	calculate_fps(t_cub3d *cub3d);
void	display_fps(t_cub3d *cub3d);
long	gettime_ms(void);
int		limit_fps(t_cub3d *cub3d);
void	update_delta_time(t_cub3d *cub3d);

// ============================================================================
// INPUT HANDLING FUNCTIONS
// ============================================================================

int		check_any_key_pressed(t_cub3d *cub3d);
int		handle_close(t_cub3d *cub3d);
int		handle_direction(t_cub3d *cub3d);
int		handle_direction_left(t_cub3d *cub3d);
int		handle_direction_right(t_cub3d *cub3d);
int		handle_keypress(int keycode, t_cub3d *cub3d);
int		handle_keyrelease(int keycode, t_cub3d *cub3d);
int		handle_loop(t_cub3d *cub3d);
int		handle_mouse_move(int x, int y, t_cub3d *cub3d);
int		handle_movement(t_cub3d *cub3d);
int		handle_movement_strafe(t_cub3d *cub3d);
void	refresh_image(t_cub3d *cub3d);
void	rotate_player_mouse(t_cub3d *cub3d, double angle);

// ============================================================================
// INITIALIZATION FUNCTIONS
// ============================================================================

void	init(t_cub3d *cub3d);
void	init_minilibx(t_cub3d *cub3d);

// ============================================================================
// MAP PARSING AND VALIDATION FUNCTIONS
// ============================================================================

int		check_adjacent(int y, int x, char **map, char new);
t_point	*check_char_remaining(char **work_map, char c);
int		count_islands(t_cub3d *cub3d, char **work_map);
t_point	find_player_position(t_cub3d *cub3d, char **map);
int		flood_fill(char ***tab, t_point current, char to_fill, char new);
int		flood_fill_z(char ***map, t_point here, char to_fill);
void	ft_check_letter(t_cub3d *cub3d);
char	**map_cpy(char **old);
void	replace_portals_by_zero(char ***map);

// ============================================================================
// MATHEMATICAL UTILITY FUNCTIONS
// ============================================================================

double	ft_abs(double nb);

// ============================================================================
// CAMERA FUNCTIONS
// ============================================================================

void	calc_camera_plane(t_cub3d *cub3d);

// ============================================================================
// MEMORY MANAGEMENT FUNCTIONS
// ============================================================================

void	free_map(char **map);
void	ft_bzero(void *s, int n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
void	secure_free(void *data);
int		try_to_open(char *path);


// ============================================================================
// MINIMAP FUNCTIONS
// ============================================================================

int		alpha_blend(int bg_color, int fg_color, double alpha);
int		blend_color_component(int bg_color, int fg_color, int alpha_int,
			int inv_alpha);
void	calculate_world_pos(double *world_x, double *world_y,
			t_minimap_calc *calc, t_minimap_screen *screen);
void	draw_minimap(t_cub3d *cub3d);
void	draw_minimap_background(t_cub3d *cub3d, int center_x, int center_y);
void	draw_minimap_pixel(t_cub3d *cub3d, int x, int y, int radius);
void	draw_minimap_pixel_optimized(t_cub3d *cub3d, t_pixel_draw *pixel);
void	draw_minimap_player(t_cub3d *cub3d, int center_x, int center_y);
void	draw_minimap_portals(t_cub3d *cub3d, int center_x, int center_y);
void	draw_minimap_walls(t_cub3d *cub3d, int center_x, int center_y);
void	draw_triangle_line(t_cub3d *cub3d, t_triangle_draw *draw);
int		get_pixel_color(t_img *img, int x, int y);
int		get_triangle_half_width(int y);
void	init_minimap_calc(t_cub3d *cub3d, t_minimap_calc *calc);
int		is_arrow_border(int x, int y);
int		is_arrow_pixel(int x, int y);
int		is_point_in_circle(int x, int y, int radius);
int		is_portal_at_pos(t_cub3d *cub3d, double world_x, double world_y);
int		is_wall_at_pos(t_cub3d *cub3d, double world_x, double world_y);
void	rotate_point(double *x, double *y, double angle);

// ============================================================================
// PIXEL DRAWING FUNCTIONS
// ============================================================================

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// ============================================================================
// PORTAL FUNCTIONS
// ============================================================================

void	check_correspondance(t_cub3d *cub3d);
t_prtl	find_a_portal(t_cub3d *cub3d, char **map);
t_point	find_correspondance(t_cub3d *cub3d, int tmp_y, int tmp_x);
void	free_portal_sprites(t_cub3d *cub3d);
void	ft_check_portals(t_cub3d *cub3d);
void	init_prtl_sprites(t_cub3d *cub3d);
char	is_portal(t_cub3d *cub3d);
void	set_direction(t_cub3d *cub3d, char dir);
void	set_prtls(t_cub3d *cub3d);
void	teleportation(t_cub3d *cub3d, t_prtl portal);
int		tp_already_set(t_cub3d *cub3d, char name);
void	update_portal_animations(t_cub3d *cub3d);

// ============================================================================
// RAYCASTING FUNCTIONS
// ============================================================================

double	calc_perpendicular_wall_distance(t_dda *dda, double ray_dir_x,
			double ray_dir_y, t_cub3d *cub3d);
void	cast_single_ray(t_cub3d *cub3d, int screen_x);
void	init_dda_params(t_cub3d *cub3d, double ray_dir_x, double ray_dir_y,
			t_dda *dda);
void	init_step_and_side_dist(t_dda *dda, double ray_dir_x,
			double ray_dir_y, t_cub3d *cub3d);
void	init_step_and_side_dist_y(t_dda *dda, double ray_dir_y,
			t_cub3d *cub3d);
void	perform_dda_algorithm(t_cub3d *cub3d, t_dda *dda);
void	perform_dda_step(t_dda *dda);
void	raycast(t_cub3d *cub3d);

// ============================================================================
// RENDERING FUNCTIONS
// ============================================================================

void	apply_fc_texture(t_cub3d *cub3d, t_texture_img *texture,
			t_fc_coords *coords);
void	calc_line_bounds(double perp_wall_dist, int *draw_start, int *draw_end);
void	draw_wall_pixels(t_cub3d *cub3d, int screen_x, int draw_start,
			int draw_end);
void	draw_wall_slice(t_cub3d *cub3d, int screen_x, double perp_wall_dist,
			t_dda *dda);
void	render_ceiling_texture(t_cub3d *cub3d, int screen_x, int draw_start);
void	render_fc_colors(t_cub3d *cub3d, int screen_x,
			int draw_start, int draw_end);
void	render_fc_pixel(t_cub3d *cub3d, int screen_x, int y,
			t_texture_img *texture);
void	render_fc_textures(t_cub3d *cub3d, int screen_x,
			int draw_start, int draw_end);
void	render_floor_texture(t_cub3d *cub3d, int screen_x, int draw_end);
void	render_ceiling_color(t_cub3d *cub3d, int screen_x, int draw_start);
void	render_floor_color(t_cub3d *cub3d, int screen_x, int draw_end);

// ============================================================================
// STRING UTILITY FUNCTIONS
// ============================================================================

int		ft_atoi(char *str);
int		ft_isdigit(char c);
char	**ft_split(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char *dest, char *str);
char	*ft_strdup(char *s);
char	*ft_strndup(char *str, int n);
int		ft_tablen(char **tab);
int		in_map(char c);
int		is_letter(char c);
int		is_lowercase(char c);
int		is_nbr(char *str);
int		is_player_spawn(char c);
int		only_numbers(char *str);
int		skip_letter(char current, char next);
void	skip_spaces(char *str, int *i);
char	safe_map_access(t_cub3d *cub3d, int y, int x);

// ============================================================================
// TEXTURE FUNCTIONS
// ============================================================================

void	calc_texture_coordinates(t_cub3d *cub3d, t_dda *dda,
			t_texture_calc *tex_calc, double perp_wall_dist);
void	calc_texture_step_pos(t_texture_calc *tex_calc, int draw_start);
void	draw_single_texture_pixel(t_cub3d *cub3d, int screen_x, int y,
			t_texture_calc *tex_calc);
void	draw_textured_wall_pixels(t_cub3d *cub3d, int screen_x,
			t_texture_calc *tex_calc, int draw_params[2]);
void	free_textures(t_cub3d *cub3d);
int		get_texture_pixel_color(t_texture_img *texture, int x, int y);
void	init_texture_draw_params(t_texture_calc *tex_calc,
			int draw_params[2], int *tex_height, int *draw_bounds[2]);
void	load_all_textures(t_cub3d *cub3d);
int		load_texture(t_cub3d *cub3d, t_texture_img *tex_img, char *path);
void	select_wall_texture(t_cub3d *cub3d, t_dda *dda,
			t_texture_calc *tex_calc);
void	select_prtl_texture(t_cub3d *cub3d, t_texture_calc *tex_calc,
			char map_char);
void	select_wall_normal_texture(t_cub3d *cub3d, t_dda *dda,
			t_texture_calc *tex_calc);
int		load_portal_texture(t_cub3d *cub3d);

#endif
