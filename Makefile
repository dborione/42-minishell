NAME	= minishell

CC 		= clang

CFLAGS	= -Wall -Wextra #-Werror

RM		= rm -f

FTS_DIR = src/

FTS		= $(wildcard src/*/*.c)

OBJ_DIR	= obj/

LIB		= ./src/minishell.h

# Colors
YELLOW	= \033[1;33m
GREEN	= \033[1;32m
BLUE	= \033[0;36m
DEFAULT	= \033[0;0m

${OBJ_DIR}%.o:	${FTS_DIR}%.c
				@mkdir -p ${@D}
				@${CC} ${CFLAGS} -c $< -o $@

OBJS	= $(patsubst ${FTS_DIR}%.c, ${OBJ_DIR}%.o, ${FTS})

${NAME}:	${OBJS}
		@echo "${BLUE} [Make] ${YELLOW} Building !"
		@make -C ./libft/
		@$(CC) ${CFLAGS} -o $@ -I ${LIB} $^ -L libft/ -lft -lreadline
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"

all:	${NAME}

clean:
		@echo "${BLUE} [Make] ${YELLOW} Cleaning !"
		@make -C ./libft/ clean
		@${RM} ${OBJS}
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"

fclean:
		@echo "${BLUE} [Make] ${YELLOW} Full Cleaning !"
		@make -C ./libft/ fclean
		@${RM} ${NAME} ${OBJS}
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"

re: fclean all

.PHONY: all clean fclean re