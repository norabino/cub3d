/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 18:06:11 by gicomlan          #+#    #+#             */
/*   Updated: 2025/07/08 14:08:43 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Fonction pour calculer la largeur maximale de la carte
int	get_max_width(char **map)
{
    int	i;
    int	max_width;
    int	current_width;

    i = 0;
    max_width = 0;
    while (map[i])
    {
        current_width = ft_strlen(map[i]);
        if (current_width > max_width)
            max_width = current_width;
        i++;
    }
    return (max_width);
}

int	fill(char **tab, t_point size, t_point current, char to_fill)
{
    // Vérification des limites de la carte
    if ((current.y < 0) || (current.x < 0) || (current.y >= size.y))
        return (0); // Sortie de carte = erreur
    
    // Vérifier si on dépasse la largeur de cette ligne spécifique
    if (current.x >= (int)ft_strlen(tab[current.y]))
        return (0); // Sortie de ligne = erreur
    
    // Si on est sur un bord et que c'est un espace accessible
    if ((current.x == 0 || current.y == 0 || 
         current.x == (int)ft_strlen(tab[current.y]) - 1 || current.y == size.y - 1)
        && (tab[current.y][current.x] == '0' || ft_is_letter(tab[current.y][current.x])))
        return (0); // Carte ouverte sur les bords
    
    // Si c'est un mur ou déjà visité
    if (tab[current.y][current.x] == '1' || tab[current.y][current.x] == 'F')
        return (1);
    
    // Si c'est un espace vide - ERREUR
    if (tab[current.y][current.x] == ' ')
        return (0);
    
    // Si ce n'est pas le caractère à remplir, on s'arrête
    if (tab[current.y][current.x] != to_fill)
        return (1);
    
    // Marquer comme visité
    tab[current.y][current.x] = 'F';
    
    // Vérifier récursivement les 4 directions
    if (!fill(tab, size, (t_point){current.x - 1, current.y}, to_fill) ||
        !fill(tab, size, (t_point){current.x + 1, current.y}, to_fill) ||
        !fill(tab, size, (t_point){current.x, current.y - 1}, to_fill) ||
        !fill(tab, size, (t_point){current.x, current.y + 1}, to_fill))
        return (0);
    
    return (1);
}

int	flood_fill(char **tab, t_point size, t_point begin)
{
    return (fill(tab, size, begin, tab[begin.y][begin.x]));
}

// Fonction pour vérifier qu'aucun F ne touche un espace
int	check_no_space_adjacent(char **tab, t_point size)
{
    int i, j;
    int line_length;
    
    i = 0;
    while (i < size.y)
    {
        line_length = ft_strlen(tab[i]);
        j = 0;
        while (j < line_length)
        {
            if (tab[i][j] == 'F')
            {
                // Vérifier les 4 directions adjacentes en tenant compte des longueurs
                if ((j > 0 && tab[i][j-1] == ' ') ||
                    (j < line_length - 1 && tab[i][j+1] == ' ') ||
                    (i > 0 && j < (int)ft_strlen(tab[i-1]) && tab[i-1][j] == ' ') ||
                    (i < size.y - 1 && j < (int)ft_strlen(tab[i+1]) && tab[i+1][j] == ' '))
                    return (0); // Erreur : F touche un espace
            }
            j++;
        }
        i++;
    }
    return (1);
}

// Fonction pour trouver la position du joueur
t_point	find_player_position(char **map, t_point size)
{
    int i, j;
    int line_length;
    
    i = 0;
    while (i < size.y)
    {
        line_length = ft_strlen(map[i]);
        j = 0;
        while (j < line_length)
        {
            if (ft_is_letter(map[i][j]))
                return ((t_point){j, i});
            j++;
        }
        i++;
    }
    return ((t_point){-1, -1}); // Joueur non trouvé
}
