NAME = cub3D
CC = cc
SRC = \
	src/main.c \
	\
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c \
	\
	src/parsing/check_and_set_file.c \
	src/parsing/check_colors_0.c \
	src/parsing/check_colors_1.c \
	src/parsing/check_map.c \
	src/parsing/check_textures_0.c \
	src/parsing/check_textures_1.c \
	src/parsing/flood_fill.c \
	src/parsing/init.c \
	src/parsing/open_file.c \
	\
	src/utils/ft_split.c \
	src/utils/free.c \
	src/utils/memory.c \
	src/utils/monitoring_utils.c \
	src/utils/str_utils_0.c \
	src/utils/str_utils_1.c \
	src/utils/str_utils_2.c \
	src/utils/str_utils_3.c \
	src/utils/str_utils_4.c \
	src/utils/time.c \
	src/utils/fps_utils.c \
	\
	src/raycasting/hook.c \
	src/raycasting/hook2.c \
	src/raycasting/hook3.c \
	src/raycasting/mouse.c \
	src/raycasting/minimap.c \
	src/raycasting/minimap_utils.c \
	src/raycasting/minimap_alpha.c \
	src/raycasting/minimap_draw.c \
	src/raycasting/init_mlx.c \
	src/raycasting/pixel_utils.c \
	src/raycasting/raycasting.c \
	src/raycasting/raycasting_utils.c \
	src/raycasting/render.c \
	src/raycasting/camera.c \
	src/raycasting/collision.c \
	src/raycasting/collision_utils.c \
	src/raycasting/textures.c \
	src/raycasting/texture_calc.c \
	src/raycasting/texture_utils.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ -g

$(NAME): minilibx $(OBJ)
	$(CC) $(OBJ) -L./MinilibX -lmlx -lXext -lX11 -lm -g -o $(NAME)


minilibx:
	@echo "Compilation de la Minilibx ..."
	@make -C MinilibX > /dev/null 2>&1

clean: clean_minilibx
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

mac: minilibx $(OBJ)
	$(CC) $(OBJ) -LMinilibX -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit -lm -g -o $(NAME)

clean_minilibx:
	@make clean -C MinilibX > /dev/null 2>&1

re: fclean all

re_mac: fclean mac

all: $(NAME)

dev : fclean clean_minilibx
	git add .; git commit -m "auto/dev"; git push --force

.PHONY: all clean fclean re re_mac dev mac minilibx clean_minilibx