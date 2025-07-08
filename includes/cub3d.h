/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:42:44 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/08 11:48:24 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# include "../src/get_next_line/get_next_line.h"

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
}	t_textures;

typedef struct s_colors
{
	int[3]	floor;
	int[3]	ceiling;
}	t_colors;

typedef	struct s_cubed
{
	t_textures	textures;
	t_colors	colors;
	char	**map;
}	t_cubed;

char	*ft_strchr(char *s, int c);
char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
char    *ft_substr(char *s, int start, int len);


char	*ft_strdup(char *s);

void	ft_perror(char *err);

char	**open_file(char *filename);
int		check_extension(char *filename);

char	**map_cpy(char **old);
void	*ft_memmove(void *dest, const void *src, size_t n);

#endif