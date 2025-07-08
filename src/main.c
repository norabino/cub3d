/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 16:00:28 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/07 19:13:45 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_cubed *cubed;
	char	**file;
	
	cubed = malloc(sizeof(t_cubed));
	if (ac != 2)
		return (ft_perror("Too few/much arguments.\nTry : ./cubed [filename]"), 1);
	if (!check_extension(av[1]))
		return (ft_perror("Must be '.cub'."), 1);
	file = open_file(av[1]);
	if (!file)
		return (1);
	cubed = set_cub3d(cubed, file);
	int i = 0;
	while (file[i])
	{
		printf("%s", file[i]);
		i++;
	}
	//if (!check_file(map))
	//	return (ft_perror("Invalid map...\n"));
	
}
