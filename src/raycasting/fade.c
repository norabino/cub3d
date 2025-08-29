/*
** Affiche un fondu noir sur l'écran pendant une courte durée
*/
#include "../../includes/cub3d.h"

void draw_fade(t_cub3d *cub3d, double alpha)
{
	int x, y;
	unsigned int current_color;
	unsigned int new_color;
	int r, g, b;
	char *pixel;
	
	for (y = 0; y < SCREEN_HEIGHT; y++)
	{
		for (x = 0; x < SCREEN_WIDTH; x++)
		{
			// Récupère la couleur actuelle du pixel
			pixel = cub3d->mlx.img->addr + (y * cub3d->mlx.img->line_length + x * (cub3d->mlx.img->bits_per_pixel / 8));
			current_color = *(unsigned int *)pixel;
			
			// Extrait les composantes RGB
			r = (current_color >> 16) & 0xFF;
			g = (current_color >> 8) & 0xFF;
			b = current_color & 0xFF;
			
			// Assombrit les couleurs selon alpha
			r = (int)(r * (1.0 - alpha));
			g = (int)(g * (1.0 - alpha));
			b = (int)(b * (1.0 - alpha));
			
			// Recompose la couleur
			new_color = (r << 16) | (g << 8) | b;
			my_mlx_pixel_put(cub3d->mlx.img, x, y, new_color);
		}
	}
}
