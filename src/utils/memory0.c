/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:04:37 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 20:54:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Fait une copie complète d'une carte */
char	**map_cpy(char **old)
{
	char	**new;
	int		len;
	int		i;

	if (!old)
		return (NULL);
	len = ft_tablen(old);
	new = calloc(len + 1, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < len && old[i])
	{
		new[i] = ft_strdup(old[i]);
		if (!new[i])
		{
			free_map(new);
			return (NULL);
		}
		i++;
	}
	new[i] = NULL;
	return (new);
}

/* Met à zéro n octets de mémoire pointés par s */
void	ft_bzero(void *s, int n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

/* Crée une copie identique d'une chaîne en mémoire */
char	*ft_strdup(char *s)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s);
	return (res);
}

/* Libère la mémoire occupée par une carte */
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		secure_free((void **)&map[i]);
		i++;
	}
	secure_free((void **)&map);
	map = NULL;
}

void	free_sprites(t_cub3d *cub3d)
{
	if (!cub3d)
		return ;
	if (cub3d->sprites)
		secure_free((void **)&cub3d->sprites);
	cub3d->sprite_count = 0;
	if (cub3d->depth_buffer.buffer)
	{
		secure_free((void **)&cub3d->depth_buffer.buffer);
		cub3d->depth_buffer.buffer = NULL;
	}
}
