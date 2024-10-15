# **************************************************************************** #;
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/13 15:08:00 by bclaeys           #+#    #+#              #
#    Updated: 2024/09/13 15:11:12 by bclaeys          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT=client
SERVER=server
CFILES_CLIENT=src/mt_client.c
CFILES_SERVER=src/mt_server.c
CC=cc
CFLAGS= -Wall -Wextra -Werror -g
INCFLAGS= -I libft -L libft -lft 
INCLUDES = -I ./libft
LIBFT=./libft/libft.a
OBJECTS_CLIENT=$(patsubst src/%.c,obj/%.o,$(CFILES_CLIENT))
OBJECTS_SERVER=$(patsubst src/%.c,obj/%.o,$(CFILES_SERVER))

all: $(LIBFT) $(MLX) obj $(SERVER) $(CLIENT)
	
$(LIBFT):
	@echo "\033[33m[ .. ] | Compiling libft...\033[0m"
	@make -s -C libft 	
	@echo "\033[33m[OK] | libft ready!\033"

$(CLIENT): $(OBJECTS_CLIENT) 
	$(CC) $(CFLAGS) -o $(CLIENT) $(OBJECTS_CLIENT) $(INCFLAGS)
	@echo "\033[33mclient created\033[0m"
	
$(SERVER): $(OBJECTS_SERVER) 
	$(CC) $(CFLAGS) -o $(SERVER) $(OBJECTS_SERVER) $(INCFLAGS)
	@echo "\033[33mserver created\033[0m"

obj: 
	@mkdir -p obj

obj/%.o:src/%.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	@rm -rf obj
	@if [ -d "obj" ]; then rmdir obj/; \
	fi
	@make -s $@ -C libft
	@echo "\033[33mAll object files, dependency files, archive files and test files removed.\033[0m"

fclean: clean
	@rm -rf $(CLIENT)
	@rm -rf $(SERVER)
	@make -s $@ -C libft
	@echo "\033[33mBinary removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re test libft obj 
