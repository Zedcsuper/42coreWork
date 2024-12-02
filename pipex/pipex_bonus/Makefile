PROG = pipex
SRCS = pipex.c utils.c
OBJS = ${SRCS:.c=.o}
CC = cc
CFLAGS = -Wall -Wextra -Werror

all : $(PROG)
%.o: %.c
	$(CC) $(CFLAGS) -c -g $< -o $@
$(PROG) : $(OBJS)
	make re -C ./libft
	$(CC) $(OBJS) -Llibft -lft -o $(PROG)

clean:
	make clean -C ./libft
	rm -f $(OBJS)



fclean: clean
	make fclean -C ./libft
	rm -f $(NAME)
	rm -f $(PROG)

re: fclean all

.PHONY: all clean re fclean
