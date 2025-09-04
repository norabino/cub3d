/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 16:47:21 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/04 16:48:24 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
