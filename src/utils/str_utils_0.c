/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 01:25:54 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Copie n caractères d'une chaîne vers une nouvelle chaîne */
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

/* Compte le nombre de lignes dans un tableau de chaînes */
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

/* Cherche un caractère dans une chaîne en partant de la fin */
char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (i >= 0 && s[i] != (char)c)
		i--;
	if (i >= 0 && s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

/* Compare deux chaînes pour vérifier si elles sont identiques */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

/* Détermine le nombre de caractères à ignorer selon l'identifiant */
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
	return (1);
}
