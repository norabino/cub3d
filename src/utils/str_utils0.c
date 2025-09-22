/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:22:56 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

char	*ft_strndup(char *str, int n)
{
	char	*tab;
	int		i;

	if (n < 0)
		return (ft_strdup(str));
	tab = (char *)malloc(n + 1);
	if (!tab)
		return (NULL);
	i = 0;
	while (str[i] && i < n)
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = 0;
	return (tab);
}

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	skip_letter(char current, char next)
{
	if (current == 'N' && next == 'O')
		return (2);
	if (current == 'S' && next == 'O')
		return (2);
	if (current == 'W' && next == 'E')
		return (2);
	if (current == 'E' && next == 'A')
		return (2);
	if (current == 'P' && next == 'O')
		return (2);
	return (1);
}
