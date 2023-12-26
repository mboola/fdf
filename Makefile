#-----NAME OF EXECUTABLE
NAME	=	fdf

#-----MAIN DIRECTORIES
SRC			=	src
INCLUDE		=	include
OBJ_DIR		=	objects

#-----STATIC LIBRARIES
MINILIBX_DIR	=	minilibx-linux
MINILIBX		=	${MINILIBX_DIR}/libmlx.a
MINILIBX_LINUX	=	${MINILIBX_DIR}/libmlx_Linux.a

LIBFT_DIR		=	libft
LIBFT			=	${LIBFT_DIR}/libft.a

#-----COMPILATION FLAGS
CC				=	cc
CFLAGS			=	-Wall #-Wextra -Werror
LIBFLAGS		=	-lXext -lX11 -lm -lz
HEADERS			=	-I./${INCLUDE}
OPTIMIZATION	=	#-O3
DEBUG			=	#-g

#-----LINKING LIBRARIES
LIBFT_LINK		=	-L./${LIBFT_DIR} -lft
MINILIBX_LINK	=	-L./${MINILIBX_DIR} -lmlx -L./${MINILIBX_DIR} -lmlx_Linux -lXext -lX11 -lm -lz

#-----FILES
FDF_HEADER	=	${INCLUDE}/ft_fdf.h

#-----HERE GOES ALL THE FILES USED IN THIS PROJECT IN SRC
SRC_FILES	=	${SRC}/main.c ${SRC}/read_data.c ${SRC}/main_loop.c
#-----------------------------

#-----RULE TO GET THE .O COMPILED
OBJ_FILES = ${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${SRC_FILES}}}

${OBJ_DIR}/%.o: ${SRC}/%.c ${FDF_HEADER} Makefile
	$(CC) ${CFLAGS} ${HEADERS} ${OPTIMIZATION} -c $< -o $@ ${DEBUG}

#-----RULES
all: ${LIB_DIR} ${OBJ_DIR} ${MINILIBX} ${LIBFT} ${NAME}

${NAME}: ${OBJ_FILES}
	@echo "Compilating fdf."
	${CC} ${OBJ_FILES} ${LIBFT_LINK} ${MINILIBX_LINK} -o $@ ${DEBUG}

${MINILIBX}:
	@echo "Compilating minilibx."
	@make -C ${MINILIBX_DIR}

${LIBFT}:
	@echo "Compilating libft."
	@make -C ${LIBFT_DIR}

#-----RULE TO CREATE THE DIRECTORIES
${LIB_DIR}:
	@echo "Creating libraries file directory."
	@mkdir -p $@

${OBJ_DIR}:
	@echo "Creating objects file directory."
	@mkdir -p $@

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

.PHONY: all clean fclean re
