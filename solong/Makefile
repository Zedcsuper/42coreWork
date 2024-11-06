CC = cc
CFLAGS = -Wall -Wextra -Werror -g
MLXFLAGS = -L ./mlx -lmlx -lXext -lX11
INCLUDE = -I./includes
LIBFT = ./libft/libft.a
VPATH = srcs:srcs/map:srcs/utils
RM = rm -rf
NAME = so_long
SRCS = srcs/hook_n_run.c srcs/init_mlx.c srcs/player.c \
	srcs/map/check_path.c srcs/map/get_map.c srcs/map/map_check.c srcs/map/render_map.c \
	srcs/utils/destroy.c srcs/utils/panic.c \
	main.c
OBJS = ${SRCS:.c=.o}
all : $(NAME)
$(NAME) : $(OBJS)
	$(MAKE) -C ./libft
	$(MAKE) -C ./mlx
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLXFLAGS) -o $(NAME)
%.c:%.o
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
clean :
	$(MAKE) clean -C ./libft
	$(RM) $(OBJS)
fclean : clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)
re : fclean all

.PHONY: all clean fclean re
