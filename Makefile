NAME = cub3D
CC = cc
SRC = \
	src/get_next_line/get_next_line.c src/get_next_line/get_next_line_utils.c \
	src/parsing/check_file.c src/parsing/open_map.c src/set.c\
	src/utils/str_utils.c src/utils/utils.c \
	src/main.c \

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) -g -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

dev :
	make fclean
	git add .; git commit -m "auto/dev"; git push
	make all

PHONY: all clean fclean re dev