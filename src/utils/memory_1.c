/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:47:21 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/05 17:44:54 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Alloue et initialise à zéro un bloc de mémoire */
void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*res;

	if (nmemb == 0 || size == 0)
	{
		res = malloc(nmemb * size * 1);
		if (!res)
			return (NULL);
		return (res);
	}
	if (nmemb * size > __INT_MAX__)
		return (NULL);
	res = (void *)malloc(nmemb * size);
	if (!res)
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}

void	*ft_memalloc(size_t size)
{
	unsigned char	*res;

	res = (unsigned char *)malloc(size);
	if (!res)
		return (NULL);
	ft_bzero(res, size);
	return (res);
}

/* Convertit un entier en chaîne de caractères */
char	*ft_alloc(int *i, int signe, long n)
{
	char	*a;

	if (n == 0)
		(*i)++;
	while (n > 0)
	{
		n /= 10;
		(*i)++;
	}
	a = ft_memalloc((*i) + signe + 1);
	if (!a)
		return (NULL);
	if (signe == 1)
	{
		a[0] = '-';
		(*i)++;
	}
	a[(*i)] = '\0';
	return (a);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;
	int		j;
	int		signe;
	long	temp;

	i = 0;
	signe = 0;
	temp = n;
	if (temp < 0)
	{
		temp *= -1;
		signe = 1;
	}
	res = ft_alloc(&i, signe, temp);
	if (!res)
		return (NULL);
	j = 1;
	while (i > j - 1 + signe)
	{
		res[i - j] = (temp % 10) + '0';
		temp /= 10;
		j++;
	}
	return (res);
}
