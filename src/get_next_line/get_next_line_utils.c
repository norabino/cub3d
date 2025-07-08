/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:19:40 by norabino          #+#    #+#             */
/*   Updated: 2025/07/08 17:36:59 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (c == 0)
		return (str + ft_strlen(str));
	while (str[i] != c && str[i])
		i++;
	if (str[i] == c)
		return ((char *)&str[i]);
	return (NULL);
}

char	*ft_substr(char *s, int start, int len, int flg)
{
	int		i;
	char	*str;

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
	if (flg)
		free(s);
	return (str);
}

void	*ft_check_join(char **s1, char **s2)
{
	if (!*s1 && !*s2)
		return (NULL);
	if (!*s1)
	{
		*s1 = (char *)malloc(1 * sizeof(char));
		if (!*s1)
			return (NULL);
		(*s1)[0] = 0;
	}
	if (!*s2)
		return (NULL);
	return ("CHECK OK");
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!ft_check_join(&s1, &s2))
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	if (s1)
		while (s1[++i] != '\0')
			str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (str);
}
