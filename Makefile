#-----NAME OF EXECUTABLE
NAME	=	fdf

#-----MAIN DIRECTORIES
SRC			=	src
INCLUDE		=	include
OBJ_DIR		=	objects
LIB_DIR		=	libraries

#-----COMPILATION FLAGS
CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
HEADERS			=	-I./${INCLUDE}
OPTIMIZATION	=	#-O3
DEBUG			=	#-g

#-----FILES
LIBFT_HEADER	=	${INCLUDE}/libft.h

#-----HERE GOES ALL THE FILES USED IN THIS PROJECT IN SRC
#-----------------------------

#-----RULE TO GET THE .O COMPILED
#OBJ_FILES = ${patsubst %.c,${OBJ_DIR}/%.o,${notdir ${SRC_FILES}}}

#${OBJ_DIR}/%.o: ${SRC}/*/%.c ${LIBFT_HEADER} Makefile
#${CC} ${CFLAGS} ${HEADERS} ${OPTIMIZATION} ${BUFFER_SIZE} -c $< -o $@ ${DEBUG}

#-----STATIC LIBRARIES
MINILIBX_DIR	=	minilibx-linux
LIBFT_DIR		=	libft

#-----RULES
all: ${LIB_DIR} ${NAME}

${NAME}: ${MINILIBX} ${LIBFT} ${OBJ_FILES}
	@echo "Compilating executable."
	${CC} ${OBJ_FILES} ${MINILIBX} ${LIBFT} -o $@ ${DEBUG}

${MINILIBX}:
	@make -C ${MINILIBX_DIR}
#here I should move the lib to libraries or something

${LIBFT}:
	@make -C ${LIBFT_DIR}
#here I should move the lib to libraries or something

#-----RULE TO CREATE THE DIRECTORIES
${LIB_DIR}:
	@echo "Creating libraries file directory."
	@mkdir -p $@

${OBJ_DIR}:
	@echo "Creating objects file directory."
	@mkdir -p $@

clean:
	rm -f ${OBJ_FILES}

fclean: clean
	@if [ -d ${LIB_DIR} ]; \
	then \
        rmdir ${LIB_DIR}; \
    fi
	@if [ -d ${OBJ_DIR} ]; \
	then \
        rmdir ${OBJ_DIR}; \
    fi
	rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
