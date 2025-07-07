/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/07 18:51:26 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../src/get_next_line/get_next_line.h"

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	int[3]	f_color;
	int[3]	c_color;
}

typedef	struct s_cubed
{
	t_textures	textures;
	char	**map;
}	t_cubed;

char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strdup(char *s);

void	ft_perror(char *err);

char	**open_map(char *filename);
int		check_extension(char *filename);

#endif