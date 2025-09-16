/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:45:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/16 16:44:15 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Passe les espaces et caractères de contrôle dans une chaîne */
void	skip_spaces(char *str, int *i)
{
	while (str[*i] && ((str[*i] >= 8 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
}

/* Vérifie si un caractère est une lettre de direction, couleur ou texture */
int	is_letter(char c)
{
	if (c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == 'F' || c == 'C' || c == 'P')
		return (1);
	return (0);
}

/* Vérifie si un caractère est un chiffre */
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

/* Vérifie si une chaîne contient uniquement des nombres et espaces */
int	only_numbers(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && str[i] != ' '
			&& str[i] != '\t' && str[i] != '\n' && str[i] != '\r')
			return (0);
		i++;
	}
	return (1);
}

/* Vérifie si une chaîne contient au moins un chiffre */
int	is_nbr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}