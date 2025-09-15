/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:54:49 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/15 16:23:44 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Affiche une erreur et termine le programme */
void	exit_error(char *err, t_cub3d *cub3d)
{
	char	*itoa;

	write(2, "Error\n", 6);
	write(2, err, ft_strlen(err));
	if (cub3d->invalid_arg)
	{
		write(2, " : \n", 4);
		itoa = ft_itoa(cub3d->nb_error_line + 1);
		write(2, itoa, ft_strlen(itoa));
		write(2, " : ", 3);
		write(2, cub3d->invalid_arg, ft_strlen(cub3d->invalid_arg));
	}
	else
		write(2, "\n", 1);
	ft_free(cub3d);
	exit(1);
}

int	try_to_open(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	close(fd);
	return (1);
} 
