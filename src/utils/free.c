/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:00:00 by norabino          #+#    #+#             */
/*   Updated: 2025/08/19 15:17:34 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	ft_free_textures_paths(t_textures *s_textures)
{
	if (s_textures->north)
	{
		free(s_textures->north);
		s_textures->north = NULL;
	}
	if (s_textures->south)
	{
		free(s_textures->south);
		s_textures->south = NULL;
	}
}

static void	ft_free_textures_paths_two(t_textures *s_textures)
{
	if (s_textures->west)
	{
		free(s_textures->west);
		s_textures->west = NULL;
	}
	if (s_textures->east)
	{
		free(s_textures->east);
		s_textures->east = NULL;
	}
}

static void	ft_free_mlx(t_mlx *s_mlx)
{
	if (s_mlx->img && s_mlx->img->img && s_mlx->mlx)
	{
		mlx_destroy_image(s_mlx->mlx, s_mlx->img->img);
		s_mlx->img->img = NULL;
	}
	if (s_mlx->img)
	{
		free(s_mlx->img);
		s_mlx->img = NULL;
	}
}

static void	ft_free_mlx_two(t_mlx *s_mlx)
{
	if (s_mlx->win && s_mlx->mlx)
	{
		mlx_destroy_window(s_mlx->mlx, s_mlx->win);
		s_mlx->win = NULL;
	}
	if (s_mlx->mlx)
	{
		mlx_destroy_display(s_mlx->mlx);
		free(s_mlx->mlx);
		s_mlx->mlx = NULL;
	}
}

void	ft_free(t_cub3d *s_cub3d)
{
	static int	g_already_freed = 0;

	if (!s_cub3d || g_already_freed)
		return ;
	g_already_freed = 1;
	ft_free_textures_paths(&s_cub3d->textures);
	ft_free_textures_paths_two(&s_cub3d->textures);
	if (s_cub3d->map)
	{
		free_map(s_cub3d->map);
		s_cub3d->map = NULL;
	}
	ft_free_mlx(&s_cub3d->mlx);
	ft_free_mlx_two(&s_cub3d->mlx);
	free(s_cub3d);
	g_already_freed = 0;
}
