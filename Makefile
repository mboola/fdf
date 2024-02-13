#------------------------------------------------------------------------------
#
#	$ Makefile $
#
#	Makefile to create an executable with the minilibx library.
#	Uses different commands based on the operative system it operates.
#
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#	NAME OF EXECUTABLE
#------------------------------------------------------------------------------
NAME	=	fdf

#------------------------------------------------------------------------------
#	MAIN DIRECTORIES
#------------------------------------------------------------------------------
SRC			=	src
INCLUDE		=	include
OBJ_DIR		=	objects

#------------------------------------------------------------------------------
#	STATIC LIBRARIES
#------------------------------------------------------------------------------
MINILIBX_DIR	=	minilibx_macos
MINILIBX		=	${MINILIBX_DIR}/libmlx.a

LIBFT_DIR		=	ft_libft
LIBFT			=	${LIBFT_DIR}/libft.a

#------------------------------------------------------------------------------
#	COMPILATION FLAGS
#------------------------------------------------------------------------------
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
MAC_LINK_FLG	=	-lmlx -framework OpenGL -framework AppKit
HEADERS			=	-I./${INCLUDE} -I./${MINILIBX_DIR}
OPTIMIZATION	=	-O3
DEBUG			=	-g
SANITIZER		=	#-fsanitize=address

#------------------------------------------------------------------------------
#	LINKING LIBRARIES
#------------------------------------------------------------------------------
LIBFT_LINK			=	-L./${LIBFT_DIR} -lft
MINILIBX_LINK_MAC	=	-L./${MINILIBX_DIR} -L./${MINILIBX_DIR} ${MAC_LINK_FLG}

#------------------------------------------------------------------------------
#	FILES
#------------------------------------------------------------------------------
FDF_HEADER	=	${INCLUDE}/ft_fdf.h ${INCLUDE}/key_definitions.h

CLEAR_STRUCTS_FILES	=	clear_structs.c
MAIN_FILES			=	main.c main_loop.c handle_keys.c set_views.c
INIT_DATA			=	init_matrices.c init_scalation.c init_translation.c \
						set_rotation_x.c set_rotation_y.c set_rotation_z.c \
						init_shape.c init_view.c init_projection.c
OPERATIONS			=	calculate_matrix.c
RASTERIZE_FILES		=	rasterize.c draw.c buffer_points.c draw_frame_buffer.c
READ_INPUT			=	read_input.c create_points.c

SRC_FILES	=	${CLEAR_STRUCTS_FILES} ${MAIN_FILES} ${INIT_DATA} ${OPERATIONS} ${RASTERIZE_FILES} ${READ_INPUT}
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
#	RULE TO GET THE .O COMPILED
#------------------------------------------------------------------------------
OBJ_FILES = ${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${SRC_FILES}}}

${OBJ_DIR}/%.o: ${SRC}/*/%.c ${FDF_HEADER} Makefile
	$(CC) ${CFLAGS} ${HEADERS} ${OPTIMIZATION} ${SANITIZER} -c $< -o $@ ${DEBUG}

#------------------------------------------------------------------------------
#	MAIN RULES TO COMPILE AND CREATE THE EXECUTABLE AND TO CLEAN IT
#------------------------------------------------------------------------------
all: ${LIB_DIR} ${OBJ_DIR} ${MINILIBX} ${LIBFT} ${NAME}

${NAME}: ${OBJ_FILES}
	@echo "Compilating fdf."
	${CC} ${SANITIZER} ${OBJ_FILES} ${LIBFT_LINK} ${MINILIBX_LINK_MAC} -o $@ ${DEBUG}

${MINILIBX}:
	@echo "Compilating minilibx."
	@make -C ${MINILIBX_DIR}

${LIBFT}:
	@echo "Compilating libft."
	@make -C ${LIBFT_DIR}

clean:
	@make clean -C ${LIBFT_DIR}
	@make clean -C ${MINILIBX_DIR}
	rm -f ${OBJ_FILES}

fclean: clean
	@if [ -d ${OBJ_DIR} ]; \
	then \
        rmdir ${OBJ_DIR}; \
    fi
	@make fclean -C ${LIBFT_DIR}
	rm -f ${NAME}

re: fclean all

#------------------------------------------------------------------------------
#	RULES TO CREATE THE DIRECTORIES
#------------------------------------------------------------------------------
${LIB_DIR}:
	@echo "Creating libraries file directory."
	@mkdir -p $@

${OBJ_DIR}:
	@echo "Creating objects file directory."
	@mkdir -p $@

.PHONY: all clean fclean re
