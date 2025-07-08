/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:28 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 17:36:17 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d *cub3d;
	char	**file;
	
	cub3d = malloc(sizeof(t_cub3d));
	if (ac != 2)
		exit_error("Too few/much arguments.\nTry : ./cub3d [filename]", cub3d);
	if (!check_extension(av[1]))
		exit_error("Must be '.cub'.", cub3d);
	file = open_file(av[1]);
	if (!file)
		return (1);
	init(cub3d);
	if (!check_and_set_file(cub3d, file))
		return (0);
}
