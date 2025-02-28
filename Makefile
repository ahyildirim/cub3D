NAME        := cub3d
CC        := gcc
FLAGS    := -Wall -Wextra -Werror -g
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################
SRCS        :=      gnl/get_next_line.c \
                          gnl/get_next_line_utils.c \
                          src/LIBFT/ft_atoi.c \
                          src/LIBFT/ft_split.c \
                          src/LIBFT/ft_strchr.c \
                          src/LIBFT/ft_strcmp.c \
                          src/LIBFT/ft_strncmp.c \
                          src/LIBFT/ft_strnstr.c \
                          src/LIBFT/ft_substr.c \
                          src/LIBFT/ft_strdup.c \
                          src/LIBFT/ft_strndup.c \
                          src/LIBFT/ft_memmove.c \
                          src/LIBFT/ft_memcpy.c \
                          src/LIBFT/ft_memset.c \
                          src/INIT/init.c \
                          src/INIT/playerinit.c \
                          src/MAP/readmap.c \
                          src/MAP/checkmap.c \
                          src/MAP/createtexture.c \
                          src/MAP/normalizemap.c \
						  src/MAP/utils.c \
                          src/main.c \
						  src/EVENTS/keyevents.c \
						  src/EVENTS/move.c \
						  src/RENDER/draw.c \
						  src/RENDER/draw_texture.c \
						  src/RENDER/raycast_dda.c \
						  src/FREE/free.c \
						  src/FREE/errorfree.c \

OBJS        := $(SRCS:.c=.o)
.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
################################################################################
#                                  Makefile  objs                              #
################################################################################
CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM		    := rm -f
UNAME		:=	$(shell uname)

ifeq ($(UNAME), Darwin)
	CFLAGS += -D__APPLE__
else ifeq ($(UNAME), Linux)
	CFLAGS += -D__linux__
else
	$(os not detected)
endif

ifeq ($(UNAME), Darwin)
$(NAME): ${OBJS}
			@echo "$(GREEN)Compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@ $(MAKE) -C mlx_linux all >/dev/null 2>&1
			@ cp ./mlx_linux/libmlx.a .
			$(CC) $(CFLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) -Lmlx_linux -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif
ifeq ($(UNAME), Linux)
$(NAME): ${OBJS}
			@echo "$(GREEN)Linux compilation ${CLR_RMV}of ${YELLOW}$(NAME) ${CLR_RMV}..."
			@chmod 777 mlx_linux/configure
			@ $(MAKE) -C mlx_linux all
			$(CC) $(CFLAGS) -g3 -o $(NAME) $(OBJS) -Imlx_linux -Lmlx_linux -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm
			@echo "$(GREEN)$(NAME) created[0m ✔️"
endif
all:		${NAME}
ifeq ($(UNAME), Darwin)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif
ifeq ($(UNAME), Linux)
clean:
			@ ${RM} *.o */*.o */*/*.o
			@ rm -rf $(NAME).dSYM >/dev/null 2>&1
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"
endif
ifeq ($(UNAME), Linux)
fclean:		clean
			@ ${RM} ${NAME}
			@ $(MAKE) -C mlx_linux clean 
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif
ifeq ($(UNAME), Darwin)
fclean:		clean
			@ ${RM} ${NAME}
			@ rm libmlx.a
			@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif
re:			fclean all
.PHONY:		all clean fclean re