/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/10 22:26:08 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
		i++;
	return (i);
}

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
	return (1);
}

void	skip_spaces(char *str, int *i)
{
	while ((str[*i] >= 8 && str[*i] <= 13) || str[*i] == ' ')
		(*i)++;
}

int	is_letter(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
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
			&& str[i] <= 8 && str[i] >= 13)
			return (0);
		i++;
	}
	return (1);
}

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	res = 0;
	if (!only_numbers(str))
		return (-1);
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (ft_isdigit(str[i]))
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	in_map(char c)
{
	if (is_letter(c) || c == '1' || c == '0')
		return (1);
	return(0);
}

t_off	collen(char **map, int y, int x)
{
	int	top;
	int	bottom;
	int	i;

	top = 0;
	bottom = 0;
	i = y;
	while (i > -1 && in_map(map[i][x]))
	{
		top++;
		i--;
	}
	i = y + 1;
	while (map[i] && map[i][x] && in_map(map[i][x]))
	{
		bottom++;
		i++;
	}
	return ((t_off){top, top + bottom});
}

t_off	linelen(char **map, int y, int x)
{
	int	right;
	int	left;
	int	i;
	
	right = 0;
	left = 0;
	i = x;
	while (i > -1 && in_map(map[y][i]))
	{
		left++;
		i--;
	}
	i = x + 1;
	while (map[y][i] && in_map(map[y][i]))
	{
		right++;
		i++;
	}
	return ((t_off){left, left + right});
}
