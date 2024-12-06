CC = cc -std=gnu99
CFLAGS = -Wall -Wextra -Werror
PRINTF = libs/ft_printf/libftprintf.a

SERVER_SRC = srcs/server.c
CLIENT_SRC = srcs/client.c 

SERVER_OBJ = srcs/server.o
CLIENT_OBJ = srcs/client.o

all: server client

server: $(SERVER_OBJ) $(PRINTF)
	@$(CC) $(CFLAGS) $(SERVER_OBJ) \
	libs/ft_printf/libftprintf.a \
	\
	-o server

client: $(CLIENT_OBJ) $(PRINTF)
	@$(CC) $(CFLAGS) $(CLIENT_OBJ) \
	libs/ft_printf/libftprintf.a \
	\
	-o client

%.o: %.c
	$(CC) $(CFLAGS) -c \
	-I./inc \
	-I./libs/ft_printf $< -o $@

$(PRINTF):
	@make -sC libs/ft_printf

clean:
	@make fclean -sC libs/ft_printf
	@rm -f $(SERVER_OBJ) $(CLIENT_OBJ)

fclean: clean
	rm -rf $(NAME) server client

re: fclean all
