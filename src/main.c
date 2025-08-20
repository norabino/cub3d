/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:28 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/20 15:28:20 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_parsing_init(t_cub3d *cub3d, int ac, char **av)
{
	char	**file;

	if (ac != 2)
		exit_error("Too few/much arguments.\nTry : ./cub3d [filename]", cub3d);
	if (!check_extension(cub3d, av[1]))
		exit_error("Must be '.cub'.", cub3d);
	file = open_file(cub3d, av[1]);
	check_and_set_file(cub3d, file);
	free_map(file);
}

int	main(int ac, char **av)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (1);
	init(cub3d);
	ft_parsing_init(cub3d, ac, av);
	init_mlx(cub3d);
	raycast(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
		cub3d->mlx.img->img, 0, 0);
	mlx_hook(cub3d->mlx.win, 17, 1L << 17, handle_close, cub3d);
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, handle_keypress, cub3d);
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, handle_keyrelease, cub3d);
	mlx_loop_hook(cub3d->mlx.mlx, handle_loop, cub3d);
	mlx_loop(cub3d->mlx.mlx);
	return (0);
}
