/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:45:00 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/22 18:23:07 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	skip_spaces(char *str, int *i)
{
	while (str[*i] && ((str[*i] >= 8 && str[*i] <= 13) || str[*i] == ' '))
		(*i)++;
}

int	is_letter(char c)
{
	if (c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == 'F' || c == 'C' || c == 'P')
		return (1);
	return (0);
}

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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
