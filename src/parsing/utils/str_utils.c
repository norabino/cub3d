/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:55:14 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 11:08:32 by jdupuis          ###   ########.fr       */
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

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0
	if (c == 0)
		return ((char *)s + ft_strlen(s));
	while (s[i] && s[i] != (char)c)
		i++;
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

char    *ft_substr(char *s, int start, int len)
{
        int  i;
        char    *str;

        if (!s)
                return (NULL);
        if (start >= ft_strlen(s))
                len = 0;
        if (ft_strlen(s) - start < len)
                len = ft_strlen(s) - start;
        str = (char *)malloc(len + 1);
        if (!str)
                return (NULL);
        i = 0;
        while (i < len && s[i])
        {
                str[i] = s[start + i];
                i++;
        }
        str[i] = 0;
        return (str);
}
