CC = cc
CFLAGS = -Wall -Wextra -Werror
NAMES = server
NAMESB = server_bonus
NAMEC = client
NAMECB = client_bonus
PRINTF = ./ft_printf/libftprintf.a
SRCC = src/client.c
SRCCB = src/client_bonus.c

SRCS = src/server.c
SRCSB = src/server_bonus.c
OBJC = $(SRCC:%.c=%.o)
OBJCB = $(SRCCB:%.c=%.o)
OBJS = $(SRCS:%.c=%.o)
OBJSB = $(SRCSB:%.c=%.o)
RM = rm -rf
INCLUDE = -I ./include

all: $(NAMEC) $(NAMES)

$(NAMEC): $(OBJC)
	$(MAKE) -C ft_printf
	$(CC) $(CFLAGS) $(OBJC) $(INCLUDE) $(PRINTF) -o $@
$(NAMES): $(OBJS)
	$(MAKE) -C ft_printf
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(PRINTF) -o $@
$(NAMECB): $(OBJCB)
	$(MAKE) -C ft_printf
	$(CC) $(CFLAGS) $(OBJCB) $(INCLUDE) $(PRINTF) -o $@
$(NAMESB): $(OBJSB)
	$(MAKE) -C ft_printf
	$(CC) $(CFLAGS) $(OBJSB) $(INCLUDE) $(PRINTF) -o $@
bonus : $(NAMECB) $(NAMESB)

clean : 
	$(MAKE) clean -C ft_printf
	$(RM) $(OBJC)
	$(RM) $(OBJS)
	$(RM) $(OBJSB)
	$(RM) $(OBJCB)
fclean : clean
	$(MAKE) fclean -C ft_printf
	$(RM) $(NAMEC)
	$(RM) $(NAMES)
	$(RM) $(NAMESB)
	$(RM) $(NAMECB)
re : fclean all
.PHONY: all clean fclean re
