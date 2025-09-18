/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_invalid_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 20:53:27 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 17:17:13 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	ft_check_invalid_line(t_cub3d *cub3d, int *idx)
{
	int	i;
	int	j;

	i = 0;
	while (cub3d->file[*idx] && !ft_search(cub3d->file[*idx], '1'))
		(*idx)++;
	while (i < *idx)
	{
		j = 0;
		skip_spaces(cub3d->file[i], &j);
		if (cub3d->file[i][j] == '\0')
		{
			i++;
			continue ;
		}
		if (!is_letter(cub3d->file[i][j]))
		{
			cub3d->invalid_arg = ft_strdup(cub3d->file[i]);
			cub3d->nb_error_line = i;
			exit_error("Invalid line", cub3d);
		}
		i++;
	}
}
