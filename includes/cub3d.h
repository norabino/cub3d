/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 14:24:12 by jdupuis          ###   ########.fr       */
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
// 1. CORE SYSTEM FUNCTIONS
// ============================================================================

// --- Error Management ---
void	exit_error(char *err, t_cub3d *cub3d);
void	ft_free(t_cub3d *s_cub3d);

// --- Initialization ---
void	init(t_cub3d *cub3d);
void	init_colors(t_cub3d *cub3d);
void	init_minilibx(t_cub3d *cub3d);
void	init_minimap_calc(t_cub3d *cub3d, t_minimap_calc *calc);
void	init_mouse(t_cub3d *cub3d);
void	init_prtl_sprites(t_cub3d *cub3d);
void	init_sprites(t_cub3d *cub3d);
void	init_sprites_struct(t_cub3d *cub3d);
void	init_time(t_cub3d *cub3d);
void	init_view(t_cub3d *cub3d);
void	init_zbuffer(t_cub3d *cub3d);

// --- Memory Management ---
void	*ft_calloc(size_t nmemb, size_t size);
void	free_map(char **map);
void	free_portal_paths(t_cub3d *cub3d);
void	free_portal_sprites(t_cub3d *cub3d);
void	free_sprites(t_cub3d *cub3d);
void	free_textures(t_cub3d *cub3d);
void	ft_bzero(void *s, int n);
void	secure_free(void **data);

// --- Time & Performance ---
void	calculate_fps(t_cub3d *cub3d);
void	display_fps(t_cub3d *cub3d);
long	gettime_ms(void);
int		limit_fps(t_cub3d *cub3d);
void	update_delta_time(t_cub3d *cub3d);

// ============================================================================
// 2. INPUT/OUTPUT SYSTEM
// ============================================================================

// --- Event Handlers ---
int		handle_close(t_cub3d *cub3d);
int		handle_keypress(int keycode, t_cub3d *cub3d);
int		handle_keyrelease(int keycode, t_cub3d *cub3d);
int		handle_loop(t_cub3d *cub3d);
int		handle_mouse_move(int x, int y, t_cub3d *cub3d);

// --- Input Processing ---
int		check_any_key_pressed(t_cub3d *cub3d);
int		handle_direction(t_cub3d *cub3d);
int		handle_direction_left(t_cub3d *cub3d);
int		handle_direction_right(t_cub3d *cub3d);
int		handle_movement(t_cub3d *cub3d);
int		handle_movement_strafe(t_cub3d *cub3d);

// --- Display Management ---
void	refresh_image(t_cub3d *cub3d);
void	rotate_player_mouse(t_cub3d *cub3d, double angle);

// ============================================================================
// 3. FILE PARSING & CONFIGURATION
// ============================================================================

// --- File Operations ---
int		count_file_lines(int fd);
char	**open_file(t_cub3d *cub3d, char *filename);
void	read_file_lines(char **file, int fd);

// --- Parsing Functions ---
void	parse_config_file(t_cub3d *cub3d, int ac, char **av);
int		parse_color_line(t_cub3d *cub3d, int i);
int		parse_texture_line(t_cub3d *cub3d, int i);
int		process_color_line(t_cub3d *cub3d, int i);
int		process_texture_line(t_cub3d *cub3d, int i);

// --- Validation Functions ---
int		all_text_set(t_cub3d *cub3d);
int		check_extension(char *filename, char *ext);
int		extract_filename_from_line(char *line, int j, char **filename);
void	ft_check_invalid_line(t_cub3d *cub3d, int *idx);
int		ft_check_map(t_cub3d *cub3d, int *idx_line);
int		validate_all_colors(t_cub3d *cub3d, int *idx);
int		validate_all_textures(t_cub3d *cub3d, int *idx);
int		validate_config_file(t_cub3d *cub3d);
void	validate_colors_complete(t_cub3d *cub3d);

// --- Assignment Functions ---
void	assign_color_values(t_cub3d *cub3d, char **split, char c);
void	assign_texture(char c, char *sub, t_cub3d *cub3d);
void	process_texture_path_found(t_cub3d *cub3d, int j, int z, int i);
void	set_ceiling(t_cub3d *cub3d, char **split);
void	set_floor(t_cub3d *cub3d, char **split);
void	set_texture(char c, int j, char *line, t_cub3d *cub3d);

// ============================================================================
// 4. MAP MANAGEMENT & COLLISION
// ============================================================================

// --- Collision Detection ---
int		check_bottom_corners(t_cub3d *cub3d, double x, double y);
int		check_corner_positions(t_cub3d *cub3d, double x, double y);
int		check_map_bounds(t_cub3d *cub3d, double x, double y);
int		is_valid_position(t_cub3d *cub3d, double x, double y);
int		is_wall_at_position(t_cub3d *cub3d, double x, double y);

// --- Map Processing ---
int		check_adjacent(int y, int x, char **map, char new);
t_point	*check_char_remaining(char **work_map, char c);
int		count_islands(t_cub3d *cub3d, char **work_map);
t_point	find_player_position(t_cub3d *cub3d, char **map);
int		flood_fill(char ***tab, t_point current, char to_fill, char new);
int		flood_fill_z(char ***map, t_point here, char to_fill);
void	ft_check_letter(t_cub3d *cub3d);
char	**map_cpy(char **old);
void	replace_portals_by_zero(char ***map);

// --- Player Movement ---
int		move_player(t_cub3d *cub3d, double delta_x, double delta_y);

// ============================================================================
// 5. RENDERING SYSTEM
// ============================================================================

// --- Camera & View ---
void	calc_camera_plane(t_cub3d *cub3d);

// --- Raycasting ---
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
void	raycast(t_cub3d *cub3d);

// --- Wall Rendering ---
void	calc_line_bounds(double perp_wall_dist, int *draw_start, int *draw_end);
void	draw_wall_slice(t_cub3d *cub3d, int screen_x, double perp_wall_dist,
			t_dda *dda);

// --- Floor/Ceiling Rendering ---
void	apply_fc_texture(t_cub3d *cub3d, t_txt_i *texture,
			t_fc_coords *coords);
void	render_ceiling_color(t_cub3d *cub3d, int screen_x, int draw_start);
void	render_ceiling_texture(t_cub3d *cub3d, int screen_x, int draw_start);
void	render_fc_colors(t_cub3d *cub3d, int screen_x,
			int draw_start, int draw_end);
void	render_fc_pixel(t_cub3d *cub3d, int screen_x, int y,
			t_txt_i *texture);
void	render_fc_textures(t_cub3d *cub3d, int screen_x,
			int draw_start, int draw_end);
void	render_floor_color(t_cub3d *cub3d, int screen_x, int draw_end);
void	render_floor_texture(t_cub3d *cub3d, int screen_x, int draw_end);

// --- Pixel Drawing ---
void	draw_transparent_pixel(t_cub3d *cub3d, int x, int y, int color);
int		get_pixel_color(t_img *img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// ============================================================================
// 6. SPRITE SYSTEM
// ============================================================================

// --- Sprite Calculations ---
double	calc_sprite_distance(t_cub3d *cub3d, double sprite_x, double sprite_y);
void	calc_sprite_properties(t_cub3d *cub3d, t_sprite *sprite,
			t_sprite_calc *calc);
void	calc_sprite_screen_bounds(t_sprite_calc *calc);

// --- Sprite Culling ---
int		is_sprite_in_fov(t_cub3d *cub3d, double sprite_x, double sprite_y);
int		is_sprite_occluded(t_cub3d *cub3d, double sprite_x, double sprite_y);
int		should_cull_sprite(t_cub3d *cub3d, double sprite_x, double sprite_y);

// --- Sprite Rendering ---
void	collect_portal_sprites(t_cub3d *cub3d);
void	draw_sprite_pixels(t_cub3d *cub3d, t_sprite *sprite,
			t_sprite_calc *calc);
void	render_sprite_column(t_cub3d *cub3d, t_sprite_calc *calc,
			t_sprite_render_data *render_data);
void	render_sprites(t_cub3d *cub3d);
void	sort_sprites_by_distance(t_cub3d *cub3d);

// --- Z-Buffer Management ---
void	update_zbuffer(t_cub3d *cub3d, int x, double distance);

// --- Color Utilities ---
int		is_transparent_color(int color);

// ============================================================================
// 7. PORTAL SYSTEM
// ============================================================================

// --- Portal Detection ---
t_prtl	find_a_portal(t_cub3d *cub3d, char **map);
t_point	find_correspondance(t_cub3d *cub3d, int tmp_y, int tmp_x);
char	is_portal(t_cub3d *cub3d);

// --- Portal Management ---
void	check_correspondance(t_cub3d *cub3d);
char	*create_portal_path(char *base_path, int frame_num);
void	ft_check_portals(t_cub3d *cub3d);
void	set_direction(t_cub3d *cub3d, char dir);
void	set_prtls(t_cub3d *cub3d);
void	teleportation(t_cub3d *cub3d, t_prtl portal);
int		tp_already_set(t_cub3d *cub3d, char name);
void	update_portal_animations(t_cub3d *cub3d);

// ============================================================================
// 8. TEXTURE SYSTEM
// ============================================================================

// --- Texture Loading ---
int		count_portal_frames(t_cub3d *cub3d);
int		init_portal_arrays(t_cub3d *cub3d);
void	load_all_textures(t_cub3d *cub3d);
int		load_portal_texture(t_cub3d *cub3d);
int		load_portal_textures_part2(t_cub3d *cub3d);
int		load_texture(t_cub3d *cub3d, t_txt_i *tex_img, char *path);

// --- Texture Calculations ---
void	calc_texture_coordinates(t_cub3d *cub3d, t_dda *dda,
			t_texture_calc *tex_calc, double perp_wall_dist);
void	calc_texture_step_pos(t_texture_calc *tex_calc, int draw_start);
int		get_texture_pixel_color(t_txt_i *texture, int x, int y);

// --- Texture Selection ---
void	select_prtl_texture(t_cub3d *cub3d, t_texture_calc *tex_calc,
			char map_char);
void	select_wall_normal_texture(t_cub3d *cub3d, t_dda *dda,
			t_texture_calc *tex_calc);
void	select_wall_texture(t_cub3d *cub3d, t_dda *dda,
			t_texture_calc *tex_calc);

// --- Texture Rendering ---
void	draw_single_texture_pixel(t_cub3d *cub3d, int screen_x, int y,
			t_texture_calc *tex_calc);
void	draw_textured_wall_pixels(t_cub3d *cub3d, int screen_x,
			t_texture_calc *tex_calc, int draw_params[2]);
void	init_texture_draw_params(t_texture_calc *tex_calc,
			int draw_params[2], int *tex_height, int *draw_bounds[2]);

// ============================================================================
// 9. MINIMAP SYSTEM
// ============================================================================

// --- Color Blending ---
int		alpha_blend(int bg_color, int fg_color, double alpha);
int		blend_color_component(int bg_color, int fg_color, int alpha_int,
			int inv_alpha);

// --- Position Calculations ---
void	calculate_world_pos(double *world_x, double *world_y,
			t_minimap_calc *calc, t_minimap_screen *screen);

// --- Drawing Functions ---
void	draw_minimap(t_cub3d *cub3d);
void	draw_minimap_background(t_cub3d *cub3d, int center_x, int center_y);
void	draw_minimap_pixel(t_cub3d *cub3d, t_pixel_draw *pixel);
void	draw_minimap_player(t_cub3d *cub3d, int center_x, int center_y);
void	draw_minimap_portals(t_cub3d *cub3d, int center_x, int center_y);
void	draw_minimap_walls(t_cub3d *cub3d, int center_x, int center_y);
void	draw_triangle_line(t_cub3d *cub3d, t_triangle_draw *draw);

// --- Geometric Utilities ---
int		get_triangle_half_width(int y);
int		is_arrow_border(int x, int y);
int		is_point_in_circle(int x, int y, int radius);
int		is_portal_at_pos(t_cub3d *cub3d, double world_x, double world_y);

// ============================================================================
// 10. UTILITY FUNCTIONS
// ============================================================================

// --- Mathematical ---
double	ft_abs(double nb);

// --- String Manipulation ---
int		ft_atoi(char *str);
char	*ft_itoa(int n);
char	**ft_split(char *str, char c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcpy(char *dest, char *str);
char	*ft_strdup(char *s);
char	*ft_strndup(char *str, int n);
int		ft_tablen(char **tab);

// --- Character Validation ---
int		ft_isdigit(char c);
int		in_map(char c);
int		is_letter(char c);
int		is_lowercase(char c);
int		is_player_spawn(char c);

// --- String Validation ---
int		check_path(char *str, int i);
int		is_nbr(char *str);
int		only_numbers(char *str);

// --- String Processing ---
char	safe_map_access(t_cub3d *cub3d, int y, int x);
int		skip_letter(char current, char next);
void	skip_spaces(char *str, int *i);

// --- File Operations ---
int		try_to_open(char *path);

#endif
