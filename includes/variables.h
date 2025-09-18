/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 19:21:04 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 18:08:08 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3d.h"

#define PI 3.14159265358979323846264338327950288
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_ESC 65307
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define MOVE_SPEED 2.0
#define SENSIBILITY 3.0
#define FPS 26
#define FOV 66
#define COLLISION_MARGIN 0.05

#define MINIMAP_SIZE 150
#define MINIMAP_X 20
#define MINIMAP_Y 20
#define MINIMAP_SCALE 16.0
#define MINIMAP_COLOR_BG 0x808080
#define MINIMAP_COLOR_WALL 0x000000
#define MINIMAP_COLOR_BORDER 0x000000
#define MINIMAP_COLOR_PLAYER 0xFF0000
#define MINIMAP_COLOR_PORTAL 0x6A5ACD

#define TRANSPARENT_COLOR 0x000000
#define MAX_SPRITE_DISTANCE 1000.0
#define SPRITE_CULLING_THRESHOLD 0.5
#define MAX_SPRITES 64