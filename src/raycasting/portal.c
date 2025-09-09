/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   portal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdupuis <jdupuis@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 19:20:24 by jdupuis           #+#    #+#             */
/*   Updated: 2025/09/09 23:36:18 by jdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Vérifie si le joueur est sur un portail */
char	is_portal(t_cub3d *cub3d)
{
	int		pos_x;
	int		pos_y;
	char	map_char;

	pos_x = (int)cub3d->player.pos_x;
	pos_y = (int)cub3d->player.pos_y;
	if (cub3d->player.last_prtl_pos.x != -1
		&& (pos_x != cub3d->player.last_prtl_pos.x
			|| pos_y != cub3d->player.last_prtl_pos.y))
	{
		cub3d->player.last_prtl_pos.x = -1;
		cub3d->player.last_prtl_pos.y = -1;
	}
	map_char = safe_map_access(cub3d, pos_y, pos_x);
	if (is_lowercase(map_char))
		return (map_char);
	return (0);
}

/* Effectue la téléportation du joueur via un portail */
void	teleportation(t_cub3d *cub3d, t_prtl portal)
{
	t_point	new;
	t_point	current_pos;
	double	dist_to_p1;
	double	dist_to_p2;

	current_pos.x = (int)cub3d->player.pos_x;
	current_pos.y = (int)cub3d->player.pos_y;
	if (current_pos.x == cub3d->player.last_prtl_pos.x
		&& current_pos.y == cub3d->player.last_prtl_pos.y)
		return ;
	dist_to_p1 = sqrt(pow(cub3d->player.pos_x - portal.p1.x, 2)
			+ pow(cub3d->player.pos_y - portal.p1.y, 2));
	dist_to_p2 = sqrt(pow(cub3d->player.pos_x - portal.p2.x, 2)
			+ pow(cub3d->player.pos_y - portal.p2.y, 2));
	if (dist_to_p1 < dist_to_p2)
		new = portal.p2;
	else
		new = portal.p1;
	cub3d->player.pos_x = new.x + 0.5;
	cub3d->player.pos_y = new.y + 0.5;
	cub3d->player.last_prtl_pos = new;
}

/* Initialise un seul portail avec ses propriétés *//*
static void	init_single_portal(t_cub3d *cub3d, int i)
{
	int		j;
	char	*right_path;
	char	*join1;
	char	*join2;
	char	*num_str;

	cub3d->prtl_sprites.frames = malloc(sizeof(t_texture_img) * 16);
	if (!cub3d->prtl_sprites.frames)
		return ;
	j = -1;
	while (++j < 16)
	{
		num_str = ft_itoa(j);
		join1 = ft_strjoin(num_str, ".xpm");
		free(num_str);
		num_str = NULL;
		join2 = ft_strjoin("Portal_", join1);
		free(join1);
		join1 = NULL;
		right_path = ft_strjoin(cub3d->textures.portals, join2);
		free(join2);
		join2 = NULL;
		load_texture(cub3d, &cub3d->prtl_sprites.frames[j], right_path);
		free(right_path);
		right_path = NULL;
	}
	
}*/

int	load_portal_texture(t_cub3d *cub3d)
{
	int		i;
	int		fd;
	char	*frame_num;
	char	*temp1;
	char	*temp2;
	char	*full_path;

	// Première passe : compter le nombre de frames disponibles
	i = 0;
	cub3d->prtl_sprites.frame_counter = 0;
	while (i < 100) // Limite raisonnable pour éviter une boucle infinie
	{
		frame_num = ft_itoa(i);
		temp1 = ft_strjoin(frame_num, ".xpm");
		temp2 = ft_strjoin("/Portal_", temp1);
		full_path = ft_strjoin(cub3d->textures.portals, temp2);
		fd = open(full_path, O_RDONLY);
		free(frame_num);
		free(temp1);
		free(temp2);
		free(full_path);
		if (fd == -1)
			break;
		close(fd);
		cub3d->prtl_sprites.frame_counter++;
		i++;
	}
	
	if (cub3d->prtl_sprites.frame_counter == 0)
		return (0);
		
	// Allouer les tableaux
	cub3d->prtl_sprites.path = malloc(sizeof(char*) * (cub3d->prtl_sprites.frame_counter + 1));
	if (!cub3d->prtl_sprites.path)
		return (0);
	cub3d->prtl_sprites.frames = malloc(sizeof(t_texture_img) * cub3d->prtl_sprites.frame_counter);
	if (!cub3d->prtl_sprites.frames)
	{
		free(cub3d->prtl_sprites.path);
		return (0);
	}
	
	// Initialiser toutes les images à NULL
	i = 0;
	while (i < cub3d->prtl_sprites.frame_counter)
	{
		cub3d->prtl_sprites.frames[i].img = NULL;
		cub3d->prtl_sprites.frames[i].addr = NULL;
		i++;
	}
	
	// Deuxième passe : charger les textures
	i = 0;
	while (i < cub3d->prtl_sprites.frame_counter)
	{
		frame_num = ft_itoa(i);
		temp1 = ft_strjoin(frame_num, ".xpm");
		temp2 = ft_strjoin("/Portal_", temp1);
		cub3d->prtl_sprites.path[i] = ft_strjoin(cub3d->textures.portals, temp2);
		load_texture(cub3d, &cub3d->prtl_sprites.frames[i], cub3d->prtl_sprites.path[i]);
		free(frame_num);
		free(temp1);
		free(temp2);
		i++;
	}
	cub3d->prtl_sprites.path[cub3d->prtl_sprites.frame_counter] = NULL; // Terminer le tableau
	
	cub3d->prtl_sprites.current_frame = 0;
	cub3d->prtl_sprites.last_frame_time = 0;
	return (1);
}

/* Initialise tous les sprites de portails */
void	init_prtl_sprites(t_cub3d *cub3d)
{
	// Ne charger les sprites qu'une seule fois pour tous les portails
	if (cub3d->nb_portals > 0)
		load_portal_texture(cub3d);
}
