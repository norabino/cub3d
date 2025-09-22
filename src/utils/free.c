/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/09/22 18:21:19 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_free_textures_paths(t_textures *textures)
{
	if (textures->north)
		secure_free((void **)&textures->north);
	if (textures->south)
		secure_free((void **)&textures->south);
	if (textures->west)
		secure_free((void **)&textures->west);
	if (textures->east)
		secure_free((void **)&textures->east);
	if (textures->ceiling)
		secure_free((void **)&textures->ceiling);
	if (textures->floor)
		secure_free((void **)&textures->floor);
	if (textures->portals)
		secure_free((void **)&textures->portals);
}

static void	ft_free_mlx(t_mlx *mlx)
{
	if (mlx->img && mlx->img->img && mlx->mlx)
	{
		mlx_destroy_image(mlx->mlx, mlx->img->img);
		mlx->img->img = NULL;
	}
	if (mlx->img)
		secure_free((void **)&mlx->img);
	if (mlx->win && mlx->mlx)
	{
		mlx_destroy_window(mlx->mlx, mlx->win);
		mlx->win = NULL;
	}
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		secure_free((void **)&mlx->mlx);
	}
}

void	ft_free(t_cub3d *cub3d)
{
	static int	already_freed = 0;

	if (!cub3d || already_freed)
		return ;
	already_freed = 1;
	secure_free((void **)&cub3d->invalid_arg);
	if (cub3d->nb_portals > 0)
		free_portal_sprites(cub3d);
	free_sprites(cub3d);
	free_textures(cub3d);
	ft_free_textures_paths(&cub3d->textures);
	if (cub3d->file)
		free_map(cub3d->file);
	if (cub3d->map)
		free_map(cub3d->map);
	ft_free_mlx(&cub3d->mlx);
	secure_free((void **)&cub3d);
	already_freed = 0;
}
