/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 20:40:54 by norabino          #+#    #+#             */
/*   Updated: 2025/09/01 21:01:40 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_check_colors(t_colors *colors, char **file, int *idx)
{
	int	i;

	i = 0;
	(*idx) = 0;
	while (file[i])
	{
		process_color_line(colors, file[i], idx, i);
		i++;
	}
	verify_colors(colors);
	return (1);
}
