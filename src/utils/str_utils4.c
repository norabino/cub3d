/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 23:02:47 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/18 17:20:23 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Copie une chaîne dans une autre */
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

/* Concatène une chaîne à la fin d'une autre */
char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i])
		i++;
	j = 0;
	while (src[j])
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (dest);
}

int	check_path(char *str, int i)
{
	if (str[i] == '.' || str[i + 1] == '/')
		return (1);
	return (0);
}

char	*ft_strstr(char *str, char *finder)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (!*finder)
		return (str);
	while (str[i] != '\0')
	{
		if (str[i] == finder[j])
			j++;
		else
			j = 0;
		if (j == ft_strlen(finder))
			return (&str[i - j + 1]);
		i++;
	}
	return (NULL);
}

int	ft_search(char *str, char search)
{
	int	i;

	i = 0;
	skip_spaces(str, &i);
	if (str[i] == search)
		return (1);
	return (0);
}
