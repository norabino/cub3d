/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: norabino <norabino@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:07:45 by jdupuis           #+#    #+#             */
/*   Updated: 2025/07/30 17:29:09 by norabino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (!img->addr)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;	
}

void	calc_camera_plane(t_cub3d *cub3d)
{
	cub3d->view.planeX = -cub3d->player.dirY * cub3d->player.fov;
	cub3d->view.planeY = cub3d->player.dirX * cub3d->player.fov;
}

void	raycast(t_cub3d *cub3d)
{
	int	    x;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	x = 0;
	while (x < 1280)
	{
		cameraX = x * 2 / 1280 - 1;
		rayDirX = cub3d.dirX + planeX * cameraX;
	}
}

/*

Certainly! Here’s a clear step-by-step guide to imlementing raycasting in C, suitable for a simple 3D engine like Wolfenstein 3D:

---

### 1. **Map Representation**
- Use a 2D array to represent your map (walls = 1, empty space = 0).

### 2. **Player Setup**
- Store player position (`posX`, `posY`), direction (`dirX`, `dirY`), and camera plane (`planeX`, `planeY`).

### 3. **Ray Loop**
- For each vertical stripe (`x`) of the screen:
    - Calculate ray direction based on camera plane and player direction.

### 4. **DDA (Digital Differential Analyzer) Algorithm**
- Calculate step and initial side distances.
- Step through the map grid until a wall is hit.

### 5. **Calculate Distance to Wall**
- When a wall is hit, calculate the perpendicular distance from the player to the wall.

### 6. **Calculate Wall Height**
- Use the distance to determine the height of the wall slice to draw.

### 7. **Draw Wall Slice**
- Use your `my_mlx_pixel_put` function to draw vertical lines for each wall slice.

### 8. **Repeat for Each Screen Column**
- Loop through all columns to render the full scene.

---

#### **Example Pseudocode**

````c
for (int x = 0; x < screenWidth; x++)
{
    // 1. Calculate ray position and direction
    double cameraX = 2 * x / (double)screenWidth - 1;
    double rayDirX = dirX + planeX * cameraX;
    double rayDirY = dirY + planeY * cameraX;

    // 2. Which box of the map we're in
    int mapX = (int)posX;
    int mapY = (int)posY;

    // 3. Length of ray from current position to next x or y-side
    double sideDistX, sideDistY;

    // 4. Length of ray from one x or y-side to next x or y-side
    double deltaDistX = fabs(1 / rayDirX);
    double deltaDistY = fabs(1 / rayDirY);

    // 5. Step direction and initial sideDist
    int stepX, stepY;
    // ...calculate stepX, stepY, sideDistX, sideDistY...

    // 6. Perform DDA
    int hit = 0;
    while (hit == 0)
    {
        // ...jump to next map square, check for wall...
    }

    // 7. Calculate distance to wall
    double perpWallDist;
    // ...calculate...

    // 8. Calculate height of line to draw
    int lineHeight = (int)(screenHeight / perpWallDist);

    // 9. Draw the vertical stripe
    for (int y = drawStart; y < drawEnd; y++)
        my_mlx_pixel_put(&img, x, y, wallColor);
}
````

---

**Tip:**  
Start simple (just walls, no textures), then add features (textures, sprites, doors, etc.).

Let me know if you want a more detailed code example for any step!

*/