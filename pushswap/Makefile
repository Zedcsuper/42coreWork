NAME = push_swap
MAIN = push_swap.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf
SRCS = ./algorithm/sort_simple.c ./algorithm/sort_small.c ./algorithm/radix_sort.c \
	./functions/ft_atoi.c ./functions/ft_lstadd_back.c ./functions/ft_lstadd_front.c \
	./functions/ft_lstsize.c ./functions/ft_lstnew.c ./functions/ft_isdigit.c \
	./functions/ft_split.c ./functions/ft_lstlast.c \
	./operations/push.c ./operations/reverse.c ./operations/rotate.c ./operations/swap.c \
	./utilities/error.c ./utilities/utilities.c ./utilities/validation.c
OBJS = $(SRCS:.c=.o)
all : $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MAIN) $(OBJS) -o $(NAME)
#%.o: %.c
#	$(CC) $(CFLAGS) -c $< -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all

.PHONY: all clean fclean re
