CC=gcc
CFLAGS= -Wall -Werror -Wextra
AR=ar crs
RM=rm -rf
FILES= ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_strlen \
	ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
	ft_strnstr ft_strlcpy ft_strlcat ft_atoi ft_strdup\
	ft_substr ft_strjoin ft_split ft_itoa ft_strmapi \
	ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_isprint\
	ft_putnbr_fd ft_strtrim ft_memcpy ft_memmove ft_memset\
	ft_memcmp ft_memchr ft_bzero ft_calloc ft_striteri \
	trim_free  free_matrix is_onstr\
	get_next_line/get_next_line get_next_line/get_next_line_utils
BFILES= ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast \
	ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap

OBJ=$(FILES:=.o)
BOBJ=$(BFILES:=.o)
FT_PRINTF_DIR = ./ft_printf
FT_PRINTF_LIB = $(FT_PRINTF_DIR)/libftprintf.a
NAME=libft.a


all: $(NAME)

bonus: $(OBJ) $(BOBJ)
	$(AR) $(NAME) $(BOBJ)

$(NAME): $(OBJ)
	$(MAKE) -C $(FT_PRINTF_DIR)
	$(AR) $(NAME) $(OBJ) $(FT_PRINTF_DIR)/*.o

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(BOBJ)
	$(MAKE) -C $(FT_PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(FT_PRINTF_DIR) fclean

re: fclean all
.PHONY: all bonus clean fclean re
