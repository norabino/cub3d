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
	src/utils/memory.c \
	src/utils/monitoring_utils.c \
	src/utils/str_utils_0.c \
	src/utils/str_utils_1.c \
	src/utils/str_utils_2.c \
	src/utils/str_utils_3.c \
	\
	src/raycasting/hook.c \
	src/raycasting/hook2.c \
	src/raycasting/hook3.c \
	src/raycasting/init_mlx.c \
	src/raycasting/pixel_utils.c \
	src/raycasting/raycasting.c \
	src/raycasting/raycasting_utils.c \
	src/raycasting/collision.c 

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ -g

$(NAME): $(OBJ)
	$(CC) $(OBJ) -Lminilibx-linux -lmlx -lXext -lX11 -lm -g -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

dev : fclean
	git add .; git commit -m "auto/dev"; git push --force

PHONY: all clean fclean re dev