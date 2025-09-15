/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 19:56:47 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Main sprite rendering function */
void	render_sprites(t_cub3d *cub3d)
{
	int				i;
	t_sprite_calc	calc;

	if (!cub3d)
		return ;
	printf("render_sprites: Starting\n");
	collect_portal_sprites(cub3d);
	printf("render_sprites: After collect, sprite_count=%d\n", cub3d->sprite_count);
	if (!cub3d->sprites || cub3d->sprite_count <= 0)
		return ;
	sort_sprites_by_distance(cub3d);
	printf("render_sprites: After sort\n");
	i = 0;
	while (i < cub3d->sprite_count)
	{
		calc_sprite_properties(cub3d, &cub3d->sprites[i], &calc);
		calc_sprite_screen_bounds(&calc);
		draw_sprite_pixels(cub3d, &cub3d->sprites[i], &calc);
		i++;
	}
	printf("render_sprites: Done\n");
}
