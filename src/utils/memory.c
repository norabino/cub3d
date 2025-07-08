/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:04:37 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 17:37:14 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdest;
	size_t			i;

	i = 0;
	psrc = (unsigned char *)src;
	pdest = (unsigned char *)dest;
	if (pdest < psrc && (pdest != NULL || psrc != NULL))
	{
		while (n != 0)
		{
			pdest[i] = psrc[i];
			i++;
			n--;
		}
	}
	else if (pdest != NULL || psrc != NULL)
	{
		while (n != 0)
		{
			pdest[n - 1] = psrc[n - 1];
			n--;
		}
	}
	return (pdest);
}

char	**map_cpy(char **old)
{
	char	**new;
	int		len;
	int		i;

	len = ft_tablen(old);
	new = malloc(sizeof(char *) * (len + 1));
	new[len] = NULL;
	i = -1;
	while (++i < len)
		new[i] = ft_strdup(old[i]);
	return (new);
}

char	*ft_strcpy(char *dest, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(char *s)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s);
	return (res);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}