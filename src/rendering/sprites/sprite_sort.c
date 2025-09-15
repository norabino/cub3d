/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 20:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/15 19:28:31 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/cub3d.h"

/* Swap two sprites */
static void	swap_sprites(t_sprite *a, t_sprite *b)
{
	t_sprite	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/* Sort sprites by distance using bubble sort (back to front) */
void	sort_sprites_by_distance(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	swapped;

	if (!cub3d->sprites || cub3d->sprite_count <= 1)
		return ;
	i = 0;
	while (i < cub3d->sprite_count - 1)
	{
		swapped = 0;
		j = 0;
		while (j < cub3d->sprite_count - i - 1)
		{
			if (cub3d->sprites[j].distance < cub3d->sprites[j + 1].distance)
			{
				swap_sprites(&cub3d->sprites[j], &cub3d->sprites[j + 1]);
				swapped = 1;
			}
			j++;
		}
		if (!swapped)
			break ;
		i++;
	}
}
