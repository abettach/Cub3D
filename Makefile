NAME=cub3D

INC=-I./inc
FLAGS= -Wall -Werror -Wextra

LIB_MAC=  -I/usr/local/include -L/usr/local/lib -lmlx -framework OpenGL -framework AppKit
LIB=$(LIB_MAC)

SRC_PATH=./srcs/

PARSING= parsing/errors.c \
		 parsing/get_next_line_utils.c \
		 parsing/get_next_line.c \
		 parsing/parsing_color_resolution_texture.c \
		 parsing/ft_parsing.c \
		 parsing/parsing_map.c \
		 parsing/parsing_utils.c \
		 parsing/parsing.c

UTILS=  src/ft_init.c \
		src/ft_intersection1.c \
		src/ft_intersection2.c \
		src/ft_keys_draw.c \
		src/ft_mlx.c \
		src/ft_projection_utils.c \
		src/ft_save.c \
		src/ft_sprite.c \
		src/ft_utils.c

SRCS=$(PARSING) \
	 $(UTILS)

SRC=$(addprefix $(SRC_PATH), $(SRCS))
OBJ=$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@gcc $(FLAGS) $(INC) -o $(NAME) $(OBJ) $(LIB)
	@echo "\033[1;33mMake \033[1;32m\t    [OK]"
	@echo "~~~~~~~~~~~~~~~~~~~~~~"
	@echo "\033[1;32m| \033[1;33m" $(NAME) : Created ! "\033[1;32m|"
	@echo "\033[1;32m~~~~~~~~~~~~~~~~~~~~~~"

%.o: %.c
	@gcc $(FLAGS) $(INC) -o $@ -c $<

clean: $(OBJ)
	@rm -f $(OBJ)
	@echo "\033[1;33mMake clean \033[1;32m [OK]"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[1;33mMake fclean \033[1;32m[OK]"

re:
	@make fclean --no-print-directory
	@make all --no-print-directory

.PHONY: all clean fclean re