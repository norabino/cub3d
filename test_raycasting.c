/* Test unitaire pour vérifier les calculs de raycasting */
#include "includes/cub3d.h"
#include <stdio.h>

void test_camera_plane_calculation()
{
    t_cub3d cub3d;
    
    // Test avec un FOV de 66 degrés
    cub3d.player.fov = 66;
    cub3d.player.dirX = 1.0;
    cub3d.player.dirY = 0.0;
    
    calc_camera_plane(&cub3d);
    
    printf("Test FOV 66°:\n");
    printf("Direction: (%.3f, %.3f)\n", cub3d.player.dirX, cub3d.player.dirY);
    printf("Plane: (%.3f, %.3f)\n", cub3d.view.planeX, cub3d.view.planeY);
    printf("Angle: %.1f radians\n", cub3d.player.fov * PI / 180.0);
}

void test_dda_params()
{
    t_cub3d cub3d;
    t_dda dda;
    double ray_dir_x = 1.0;
    double ray_dir_y = 0.5;
    
    cub3d.player.coords = malloc(sizeof(t_point));
    cub3d.player.coords->x = 2;
    cub3d.player.coords->y = 3;
    
    init_dda_params(&cub3d, ray_dir_x, ray_dir_y, &dda);
    
    printf("\nTest DDA params:\n");
    printf("Position: (%d, %d)\n", cub3d.player.coords->x, cub3d.player.coords->y);
    printf("Ray direction: (%.1f, %.1f)\n", ray_dir_x, ray_dir_y);
    printf("Map position: (%d, %d)\n", dda.map_x, dda.map_y);
    printf("Delta distances: (%.3f, %.3f)\n", dda.delta_dist_x, dda.delta_dist_y);
    
    free(cub3d.player.coords);
}

int main()
{
    printf("=== Test des fonctions de raycasting ===\n");
    test_camera_plane_calculation();
    test_dda_params();
    printf("\n✓ Tests terminés avec succès\n");
    return 0;
}
