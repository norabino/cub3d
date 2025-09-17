/* **********************	dest[i] = '\0';
	return (dest);
}************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:45:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 16:45:00 by jdupuis          ###   ########.fr       */
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
