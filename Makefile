# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abouhlel <abouhlel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/10 17:44:09 by abouhlel          #+#    #+#              #
#    Updated: 2022/02/13 22:11:44 by abouhlel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= cub3D

# ███████╗    ██╗    ██╗         ███████╗    ███████╗
# ██╔════╝    ██║    ██║         ██╔════╝    ██╔════╝
# █████╗      ██║    ██║         █████╗      ███████╗
# ██╔══╝      ██║    ██║         ██╔══╝      ╚════██║
# ██║         ██║    ███████╗    ███████╗    ███████║
# ╚═╝         ╚═╝    ╚══════╝    ╚══════╝    ╚══════╝

FOLDER_HEADER		= headers/

FOLDER_MANDA		= srcs/mandatory/

FOLDER_BONUS		= srcs/bonus/

HEADER_FILE 		= cub3d.h

SRCS				=	check_walls.c \
						dda.c \
						init_data.c \
					 	main.c \
						moves.c \
						parsing.c \
						stock_data.c \
						check_textures.c \
						define_img.c \
						draw.c \
						errors.c \
						hooks.c \
						map_utils.c \
						memory.c \
						mini_map.c \
						minimap_limits.c \
						print_texture.c \
						raycasting.c \
						rotations.c \
						utils.c \
						wall_height.c \
						wall_textures.c 
						
SRCS_BONUS 			= 	animation.c \
						check_walls_b.c \
						main_bonus.c \
						dda_b.c \
						init_data_b.c \
						moves_b.c \
						parsing_b.c \
						stock_data_b.c \
						check_textures_b.c \
						define_img_b.c \
						draw_b.c \
						errors_b.c \
						hooks_b.c \
						map_utils_b.c \
						memory_b.c \
						mini_map_b.c \
						minimap_limits_b.c \
						print_texture_b.c \
						raycasting_b.c \
						rotations_b.c \
						utils_b.c \
						wall_height_b.c \
						wall_textures_b.c 
						
SRC_M				= $(addprefix ${FOLDER_MANDA},${SRCS})
SRC_B				= $(addprefix ${FOLDER_BONUS},${SRCS_BONUS})
HEADERS				= $(addprefix ${FOLDER_HEADER},${HEADER_FILE})

OBJS				= ${SRC_M:.c=.o}
OBJS_B				= ${SRC_B:.c=.o}

#  ██████╗     ██████╗     ███╗   ███╗    ██████╗     ██╗    ██╗
# ██╔════╝    ██╔═══██╗    ████╗ ████║    ██╔══██╗    ██║    ██║
# ██║         ██║   ██║    ██╔████╔██║    ██████╔╝    ██║    ██║
# ██║         ██║   ██║    ██║╚██╔╝██║    ██╔═══╝     ██║    ██║
# ╚██████╗    ╚██████╔╝    ██║ ╚═╝ ██║    ██║         ██║    ███████╗
#  ╚═════╝     ╚═════╝     ╚═╝     ╚═╝    ╚═╝         ╚═╝    ╚══════╝

CC					= gcc
CFLAGS  			= -Wall -Wextra -Werror -g -fsanitize=address
RM					= rm -rf
MAKE_EXT			= @make -s --no-print-directory -C

OBJ					= ${OBJS}
OBJ_B				= ${OBJS_B}

UNAME_S				= $(shell uname -s)

ifeq ($(UNAME_S),Linux)
	LIBS 			= -L ./libft -lft -lmlx -lXext -lX11
endif
ifeq ($(UNAME_S),Darwin)
	LIBS 			= -L ./libft -lft -lmlx -framework OpenGL -framework AppKit -lz
endif

COMPIL		= $(CC) $(CFLAGS) ${OBJ} $(LIBS) -o $(NAME)
COMPIL_B	= $(CC) $(CFLAGS) ${OBJ_B} $(LIBS) -o $(NAME)

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

bonus:		${OBJ_B}
			@printf $(blue)
			@printf " Generating bonus objects... %-33.33s                                 \r" $@
			@printf $(magenta)
			$(MAKE_EXT) ./libft
			@$(COMPIL_B)
			@printf "➖➖➖➖➖➖➖➖➖➖➖➖                         \n"
			@printf "💎 ENJOY THE BONUS 💎\n"
			@printf "➖➖➖➖➖➖➖➖➖➖➖➖\n"
			@printf $(reset)

re: 		fclean all

clean:
			$(MAKE_EXT) ./libft clean
			@${RM} ${OBJ} ${OBJ_B}
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

.PHONY: 	all clean fclean re bonus


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
