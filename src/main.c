/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:28 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 17:57:07 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/* Parse et valide le fichier de configuration */
void	parse_config_file(t_cub3d *cub3d, int ac, char **av)
{
	if (ac != 2)
		exit_error("Too few/much arguments.\nTry : ./cub3d [filename]",
			cub3d);
	if (!check_extension(av[1], ".cub"))
		exit_error("Wrong extension.\nMust be '.cub'.", cub3d);
	cub3d->file = open_file(cub3d, av[1]);
	validate_config_file(cub3d);
}

/* Point d'entrée principal du programme */
int	main(int ac, char **av)
{
	t_cub3d	*cub3d;

	cub3d = malloc(sizeof(t_cub3d));
	if (!cub3d)
		return (1);
	ft_bzero(cub3d, sizeof(t_cub3d));
	init(cub3d);
	parse_config_file(cub3d, ac, av);
	init_minilibx(cub3d);
	raycast(cub3d);
	mlx_put_image_to_window(cub3d->mlx.mlx, cub3d->mlx.win,
		cub3d->mlx.img->img, 0, 0);
	mlx_hook(cub3d->mlx.win, 17, 1L << 17, handle_close, cub3d);
	mlx_hook(cub3d->mlx.win, 2, 1L << 0, handle_keypress, cub3d);
	mlx_hook(cub3d->mlx.win, 3, 1L << 1, handle_keyrelease, cub3d);
	mlx_hook(cub3d->mlx.win, 6, 1L << 6, handle_mouse_move, cub3d);
	mlx_loop_hook(cub3d->mlx.mlx, handle_loop, cub3d);
	mlx_loop(cub3d->mlx.mlx);
	return (0);
}
