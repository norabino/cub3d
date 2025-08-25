/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:17:12 by norabino          #+#    #+#             */
/*   Updated: 2025/08/25 13:21:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

long	gettime_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	check_frames(t_cub3d *cub3d)
{
	if (gettime_ms() - cub3d->last_refresh >= (1 / FPS))
		return (1);
	return (0);
}

void	calculate_fps(t_cub3d *cub3d)
{
	long	current_time;
	long	elapsed_time;

	current_time = gettime_ms();
	cub3d->fps_frame_count++;
	
	elapsed_time = current_time - cub3d->fps_last_time;
	if (elapsed_time >= 1000)  // Calculer les FPS chaque seconde
	{
		cub3d->current_fps = (double)cub3d->fps_frame_count * 1000.0 / elapsed_time;
		printf("FPS: %.1f\n", cub3d->current_fps);
		cub3d->fps_frame_count = 0;
		cub3d->fps_last_time = current_time;
	}
}
