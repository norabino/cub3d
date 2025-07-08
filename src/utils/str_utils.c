/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 14:14:00 by norabino         ###   ########.fr       */
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

int	ft_is_letter(char c)
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

int	ft_atoi(char *str)
{
	int	res;
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	res = 0;
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
