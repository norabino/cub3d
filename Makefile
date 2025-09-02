NAME = cub3D
CC = cc
OBJDIR = objects

all: $(NAME)

# Main entry point
MAIN_SRC = \
	src/main.c \

# Initialization system files
INIT_SRC = \
	src/init/game_init.c \
	src/init/init_mlx.c \

# Parsing and file handling
PARSING_SRC = \
	src/parsing/check_and_set_file.c \
	src/parsing/config_validator.c \
	src/parsing/color_parser.c \
	src/parsing/color_validator.c \
	src/parsing/texture_parser.c \
	src/parsing/texture_utils.c \
	src/parsing/texture_validator.c \
	src/parsing/check_map.c \
	src/parsing/portal_parsing.c \
	src/parsing/portal_utils.c \
	src/parsing/file_utils.c \
	src/parsing/flood_fill.c \
	src/parsing/open_file.c \

# Input handling
INPUT_SRC = \
	src/input/hook.c \
	src/input/hook2.c \
	src/input/hook3.c \
	src/input/mouse.c \

# User Interface
UI_SRC = \
	src/ui/minimap.c \
	src/ui/minimap_alpha.c \
	src/ui/minimap_draw.c \
	src/ui/minimap_player.c \
	src/ui/minimap_utils.c \

# Rendering system
RENDERING_SRC = \
	src/rendering/camera.c \
	src/rendering/collision.c \
	src/rendering/collision_utils.c \
	src/rendering/floor_ceiling.c \
	src/rendering/floor_ceiling_utils.c \
	src/rendering/pixel_utils.c \
	src/rendering/portal.c \
	src/rendering/portal_textures.c \
	src/rendering/portal_utils2.c \
	src/rendering/raycasting.c \
	src/rendering/raycasting_utils.c \
	src/rendering/dda_utils.c \
	src/rendering/render.c \
	src/rendering/texture_calc.c \
	src/rendering/texture_utils.c \
	src/rendering/textures.c \

# Utility functions
UTILS_SRC = \
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
	src/utils/ft_free.c \

# Get Next Line
GNL_SRC = \
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c \

# All source files
SRC = $(MAIN_SRC) $(INIT_SRC) $(PARSING_SRC) $(INPUT_SRC) $(UI_SRC) $(RENDERING_SRC) $(UTILS_SRC) $(GNL_SRC)

OBJ = $(SRC:src/%.c=$(OBJDIR)/%.o)

$(OBJDIR)/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) -Wall -Wextra -Werror -c $< -o $@ -g

$(NAME): minilibx $(OBJ)
	$(CC) $(OBJ) -L./MinilibX -lmlx -lXext -lX11 -lm -g -o $(NAME)

minilibx:
	@echo "Compilation de la Minilibx ..."
	@make -s -C MinilibX > /dev/null 2>&1

clean_minilibx:
	@make clean -C MinilibX > /dev/null 2>&1

mac: minilibx $(OBJ)
	$(CC) $(OBJ) -LMinilibX -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit -lm -g -o $(NAME)

clean:
	rm -rf $(OBJDIR)
	@make -s clean -C MinilibX > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	@make -s clean -C MinilibX > /dev/null 2>&1

re: fclean $(NAME)

re_mac: fclean mac

dev : fclean clean_minilibx
	git add .; git commit -m "auto/dev"; git push --force

.PHONY: all clean clean_minilibx fclean re re_mac mac minilibx dev
