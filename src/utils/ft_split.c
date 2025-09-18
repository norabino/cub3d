/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:34:43 by norabino          #+#    #+#             */
/*   Updated: 2025/09/18 20:54:52 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Gère le cas où il n'y a pas de séparateur dans la chaîne */
int	ft_zerosep(char *str, char ***dst)
{
	*dst = (char **)malloc(sizeof(char *) * 2);
	if (!dst)
		return (0);
	(*dst)[0] = ft_strndup((char *)str, ft_strlen((char *)str));
	if (!(*dst)[0])
		return (free(dst), 0);
	(*dst)[1] = 0;
	return (1);
}

/* Compte le nombre de mots séparés par le caractère c */
int	ft_countwords(char const *s, int c)
{
	int	i;
	int	j;
	int	in;

	i = 0;
	j = 0;
	in = 0;
	while (s[i])
	{
		if (s[i] != (char)c && in != 1)
		{
			in = 1;
			j++;
		}
		if (s[i] == (char)c && in == 1)
			in = 0;
		i++;
	}
	return (j);
}

/* Construit une ligne en trouvant le début et la fin du mot */
void	ft_build_line(char *str, int *s, int *e, char *c)
{
	while (str[*s] == *c && str[*s])
		(*s)++;
	*e = *s;
	while (str[*e] != *c && str[*e])
		(*e)++;
}

/* Libère la mémoire du tableau de chaînes */
void	ft_free_dst(char ***dst, int *i)
{
	while ((*i)--)
		free((*dst)[*i]);
	free(*dst);
}

/* Divise une chaîne en tableau de mots selon le séparateur c */
char	**ft_split(char *str, char c)
{
	int		tab[3];
	char	**dst;

	if (!ft_strchr(str, c))
		return (ft_zerosep(str, &dst), dst);
	dst = (char **)malloc(sizeof(char *) * (ft_countwords(str, (int)c) + 1));
	if (!dst)
		return (NULL);
	tab[2] = 0;
	tab[0] = 0;
	while (str[tab[0]] && tab[2] < ft_countwords(str, (int)c))
	{
		ft_build_line((char *)str, &tab[0], &tab[1], &c);
		dst[tab[2]] = ft_strndup((char *)str + tab[0], tab[1] - tab[0]);
		if (dst[tab[2]] == NULL)
			return (ft_free_dst(&dst, &tab[2]), NULL);
		tab[0] = tab[1];
		tab[2]++;
	}
	dst[tab[2]] = 0;
	return (dst);
}
