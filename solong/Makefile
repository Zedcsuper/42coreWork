CC = cc

CFLAGS = -Wall -Wextra -Werror -g

MLXFLAGS = -L ./mlx -lmlx -lXext -lX11

INCLUDE = -I./includes

LIBFT = ./libft/libft.a

OBJ_DIR = obj_dir

RM = rm -rf

NAME = so_long

SRCS =\
	src/main.c \
	src/hook_n_run.c \
	src/init_mlx.c \
	src/check_path.c \
	src/get_map.c \
	src/map_check.c \
	src/render_map.c \
	src/player.c \
	src/destroy.c \
	src/panic.c

OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C ./mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(OBJ_DIR)/%.o: src/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./mlx
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
