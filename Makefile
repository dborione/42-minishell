NAME	= minishell

# Compilation 

CC 		= clang
CFLAGS	= -Wall -Wextra -Werror -I${LIB_DIR} -I ~/homebrew/opt/readline/include
RM		= rm -f

# Colors
YELLOW	= \033[1;33m
GREEN	= \033[1;32m
BLUE	= \033[0;36m
DEFAULT	= \033[0;0m

# Dependencies

FTS_DIR = src/
OBJ_DIR	= obj/
LIB_DIR = inc/
FTS		= $(wildcard src/*/*.c)
OBJS	= $(patsubst ${FTS_DIR}%.c, ${OBJ_DIR}%.o, ${FTS})
DEPENDS	:= $(OBJS:.o=.d)
UNAME	:= $(shell uname)

${OBJ_DIR}%.o:	${FTS_DIR}%.c
		@mkdir -p ${@D}
		@${CC} ${CFLAGS} -MMD -MP -c $< -o $@

# Rules

${NAME}:	${OBJS}
		@echo "${BLUE} [Make] ${YELLOW} Building ${DEFAULT}LIBFT${YELLOW} !${DEFAULT}"
		@make -C ./libft/
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"
		@echo "${BLUE} [Make] ${YELLOW} Building ${DEFAULT}MINISHELL${YELLOW} !${DEFAULT}"
		$(CC) ${CFLAGS} -o $@ $^ -Llibft -lft -lreadline -L ~/homebrew/opt/readline/lib
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"

all:	${NAME}

clean:
		@echo "${BLUE} [Make] ${YELLOW} Cleaning !"
		@make -C ./libft/ clean
		@${RM} ${OBJS} ${DEPENDS}
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"

fclean:
		@echo "${BLUE} [Make] ${YELLOW} Full Cleaning !"
		@make -C ./libft/ fclean
		@${RM} ${NAME} ${OBJS} ${DEPENDS}
		@echo "${BLUE} [Make] ${GREEN} Done. ${DEFAULT}"

re: fclean all

-include $(DEPENDS)

.PHONY: all clean fclean re os leaks