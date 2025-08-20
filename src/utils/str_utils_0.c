/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/08/20 16:05:01 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/*
** Copie une partie d'un texte sur un nombre limité de caractères
** Comme recopier seulement les 5 premiers mots d'une phrase
** au lieu de toute la phrase
*/
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

/*
** Compte le nombre de lignes dans un tableau de textes
** Comme compter le nombre de pages dans un livre
** en tournant chaque page une par une
*/
int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

/*
** Cherche un caractère dans un texte en partant de la fin
** Comme chercher la dernière occurrence d'une lettre
** dans un mot en lisant de droite à gauche
*/
char	*ft_strrchr(char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i] != (char)c && i >= 0)
		i--;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (NULL);
}

/*
** Compare deux textes pour voir s'ils sont identiques
** Comme comparer deux mots pour voir s'ils sont
** exactement les mêmes lettre par lettre
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] && s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

/*
** Détermine combien de lettres il faut ignorer selon le mot
** Comme savoir si on lit "NO" (2 lettres) ou juste "N" (1 lettre)
** pour reconnaître les directions North, South, East, West
*/
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
