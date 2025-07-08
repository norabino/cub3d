NAME = cub3D
CC = cc
SRC = \
	src/main.c \
	\
	src/get_next_line/get_next_line.c \
	src/get_next_line/get_next_line_utils.c \
	\
	src/parsing/check_and_set_file.c \
	src/parsing/flood_fill.c \
	src/parsing/init.c \
	src/parsing/open_file.c \
	\
	src/utils/ft_split.c \
	src/utils/memory.c \
	src/utils/str_utils.c \
	src/utils/utils.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@ -g

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

dev : fclean
	git add .; git commit -m "auto/dev"; git push --force

PHONY: all clean fclean re dev