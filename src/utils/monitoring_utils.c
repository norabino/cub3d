/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:54:49 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/09 23:08:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Affiche une erreur et termine le programme */
void	exit_error(char *err, t_cub3d *cub3d)
{
	int	i;

	(void)cub3d;
	write(2, "Error\n", 6);
	i = 0;
	while (err[i])
	{
		write(2, &err[i], 1);
		i++;
	}
	write(2, "\n", 1);
	ft_free(cub3d);
	exit(1);
}
