# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/10 17:44:09 by abouhlel          #+#    #+#              #
#    Updated: 2022/01/13 15:08:45 by abouhlel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cub3d

# ███████╗    ██╗    ██╗         ███████╗    ███████╗
# ██╔════╝    ██║    ██║         ██╔════╝    ██╔════╝
# █████╗      ██║    ██║         █████╗      ███████╗
# ██╔══╝      ██║    ██║         ██╔══╝      ╚════██║
# ██║         ██║    ███████╗    ███████╗    ███████║
# ╚═╝         ╚═╝    ╚══════╝    ╚══════╝    ╚══════╝

FOLDER_HEADER		= headers/
FOLDER				= srcs/

HEADER_FILE 		= cub3d.h

SRCS				= 	main.c \
						ft_parsing.c \
						ft_memory.c \
						ft_errors.c \
						ft_stock_data.c \

SRC					= $(addprefix ${FOLDER},${SRCS})
HEADERS				= $(addprefix ${FOLDER_HEADER},${HEADER_FILE})

OBJS				= ${SRC:.c=.o}

#  ██████╗     ██████╗     ███╗   ███╗    ██████╗     ██╗    ██╗
# ██╔════╝    ██╔═══██╗    ████╗ ████║    ██╔══██╗    ██║    ██║
# ██║         ██║   ██║    ██╔████╔██║    ██████╔╝    ██║    ██║
# ██║         ██║   ██║    ██║╚██╔╝██║    ██╔═══╝     ██║    ██║
# ╚██████╗    ╚██████╔╝    ██║ ╚═╝ ██║    ██║         ██║    ███████╗
#  ╚═════╝     ╚═════╝     ╚═╝     ╚═╝    ╚═╝         ╚═╝    ╚══════╝

CC					= gcc
CFLAGS  			= -Wall -Wextra -Werror
RM					= rm -rf
MAKE_EXT			= @make -s --no-print-directory -C

OBJ					= ${OBJS}

UNAME_S				= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS 			= -L ./libft -lft -lmlx -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	LIBS 			= -L ./libft -lft -lmlx -framework OpenGL -framework AppKit -lz
endif

COMPIL	= $(CC) $(CFLAGS) ${OBJ} $(LIBS) -o $(NAME)

# ██████╗     ██╗   ██╗    ██╗         ███████╗    ███████╗
# ██╔══██╗    ██║   ██║    ██║         ██╔════╝    ██╔════╝
# ██████╔╝    ██║   ██║    ██║         █████╗      ███████╗
# ██╔══██╗    ██║   ██║    ██║         ██╔══╝      ╚════██║
# ██║  ██║    ╚██████╔╝    ███████╗    ███████╗    ███████║
# ╚═╝  ╚═╝     ╚═════╝     ╚══════╝    ╚══════╝    ╚══════╝

$(NAME):	${OBJ}
				@printf $(blue)
				@printf "\n"
				@printf $(magenta)
				$(MAKE_EXT) ./libft
				@$(COMPIL)
				@printf $(cyan)
				@printf "➖➖➖➖➖➖➖➖➖➖➖➖\n"
				@printf "🎮 YOUR GAME IS READY 🎮\n"
				@printf "➖➖➖➖➖➖➖➖➖➖➖➖\n"
				@printf $(reset)

all:		${NAME}

%.o: %.c	$(HEADERS)
				@printf $(magenta)
				@printf "Generating cub3d objects... %-33.33s\r" $@
				@$(CC) -c $(CFLAGS) -o $@ $<
				@printf $(reset)

re: 		fclean all

clean:
			$(MAKE_EXT) ./libft clean
			@${RM} ${OBJ}
			@printf $(yellow)
			@printf "Object files have been deleted   ✅\n"
			@printf $(reset)

fclean:		clean
			$(MAKE_EXT) ./libft fclean
			@${RM} $(NAME)
			@printf $(green)
			@printf "Executable file has been deleted ✅\n"
			@printf $(red)
			@printf "✨✨ Your folder is now clean ✨✨\n"
			@printf $(reset)

.PHONY: 	all clean fclean re


#  ██████╗     ██████╗     ██╗          ██████╗     ██████╗
# ██╔════╝    ██╔═══██╗    ██║         ██╔═══██╗    ██╔══██╗
# ██║         ██║   ██║    ██║         ██║   ██║    ██████╔╝
# ██║         ██║   ██║    ██║         ██║   ██║    ██╔══██╗
# ╚██████╗    ╚██████╔╝    ███████╗    ╚██████╔╝    ██║  ██║
#  ╚═════╝     ╚═════╝     ╚══════╝     ╚═════╝     ╚═╝  ╚═╝

black 				=	"[1;30m"
red 				=	"[1;31m"
green 				=	"[1;32m"
yellow 				=	"[1;33m"
blue 				=	"[1;34m"
magenta 			=	"[1;35m"
cyan 				=	"[1;36m"
white 				=	"[1;37m"

bg_black 			=	"[40m"
bg_red 				=	"[41m"
bg_green 			=	"[42m"
bg_yellow 			=	"[43m"
bg_blue 			=	"[44m"
bg_magenta 			=	"[45m"
bg_cyan 			=	"[46m"
bg_white 			=	"[47m"

reset 				=	"[0m"

#################################################################################
#                                                                               #
#                   ##                                             #####        #
#                   ##                                             #            #
#                   ##                                           #######        #
#                   ##                                              ##          #
#       #####       ##          ####           #    #    #          ##          #
#       #           ##         #    #          #    #    #          ##          #
#     ########      ########################### #### ####           ##          #
#                                                                               #
#################################################################################
