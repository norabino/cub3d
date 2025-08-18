/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 16:17:12 by norabino          #+#    #+#             */
/*   Updated: 2025/08/18 16:30:57 by norabino         ###   ########.fr       */
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
	if (gettime_ms() - cub3d->last_refresh >= 0.016)
		return (1);
	return (0);
}
