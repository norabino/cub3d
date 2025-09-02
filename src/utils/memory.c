/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 11:04:37 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/02 07:59:35 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Déplace des données d'un endroit à un autre en mémoire
** Comme transporter des cartons d'un appartement à un autre
** en faisant attention à ne pas les faire tomber
*/
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

/*
** Fait une copie complète d'une carte
** Comme photocopier chaque page d'un livre
** pour avoir un exemplaire de secours
*/
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

/*
** Copie un texte caractère par caractère
** Comme recopier une phrase au tableau
** lettre par lettre sans faire d'erreur
*/
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

/*
** Crée une copie identique d'un texte en mémoire
** Comme faire un double d'un document important
** pour le garder en sécurité
*/
char	*ft_strdup(char *s)
{
	char	*res;

	res = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!res)
		return (NULL);
	ft_strcpy(res, s);
	return (res);
}

/*
** Libère la mémoire occupée par une carte
** Comme ranger tous les cahiers d'une étagère
** puis démonter l'étagère elle-même
*/
void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
