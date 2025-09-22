/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:17:12 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 18:59:50 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

long	gettime_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec * 1000) + (current_time.tv_usec / 1000));
}

int	limit_fps(t_cub3d *cub3d)
{
	long	current_time;

	current_time = gettime_ms();
	if ((current_time - cub3d->time.last_refresh) >= (1000 / FPS))
	{
		cub3d->time.last_refresh = current_time;
		return (1);
	}
	return (0);
}

void	calculate_fps(t_cub3d *cub3d)
{
	long	current_time;
	long	elapsed_time;

	current_time = gettime_ms();
	if (cub3d->time.fps_last_time == 0)
		cub3d->time.fps_last_time = current_time;
	cub3d->time.fps_frame_count++;
	elapsed_time = current_time - cub3d->time.fps_last_time;
	if (elapsed_time >= 1000)
	{
		if (elapsed_time > 0)
		{
			cub3d->time.current_fps = (double)cub3d->time.fps_frame_count
				* 1000.0 / elapsed_time;
		}
		cub3d->time.fps_frame_count = 0;
		cub3d->time.fps_last_time = current_time;
	}
}

void	update_delta_time(t_cub3d *cub3d, long current_time)
{
	static long	last_time = 0;

	if (last_time == 0)
		last_time = current_time;
	cub3d->time.delta_time = (current_time - last_time) / 1000.0;
	last_time = current_time;
}

void	display_fps(t_cub3d *cub3d)
{
	char	*temp_str;
	char	fps_buffer[32];
	int		fps_int;

	fps_int = (int)(cub3d->time.current_fps + 0.5);
	ft_strcpy(fps_buffer, "FPS: ");
	temp_str = ft_itoa(fps_int);
	if (temp_str)
	{
		ft_strcat(fps_buffer, temp_str);
		free(temp_str);
		mlx_string_put(cub3d->mlx.mlx, cub3d->mlx.win,
			SCREEN_WIDTH - 80, 25, 0x00FF00, fps_buffer);
	}
}
