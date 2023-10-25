NAME	= libft.a

FTS		= ./utils/src/ft_isalpha.c \
		./utils/src/ft_isdigit.c \
		./utils/src/ft_isalnum.c \
		./utils/src/ft_isascii.c \
		./utils/src/ft_isprint.c \
		./utils/src/ft_strlen.c \
		./utils/src/ft_memset.c \
		./utils/src/ft_bzero.c \
		./utils/src/ft_memcpy.c \
		./utils/src/ft_memmove.c \
		./utils/src/ft_memchr.c	\
		./utils/src/ft_strncmp.c \
		./utils/src/ft_strlcpy.c \
		./utils/src/ft_strlcat.c \
		./utils/src/ft_toupper.c \
		./utils/src/ft_tolower.c \
		./utils/src/ft_strchr.c \
		./utils/src/ft_strrchr.c \
		./utils/src/ft_memcmp.c \
		./utils/src/ft_strnstr.c \
		./utils/src/ft_atoi.c \
		./utils/src/ft_calloc.c \
		./utils/src/ft_strdup.c \
		./utils/src/ft_substr.c \
		./utils/src/ft_strjoin.c \
		./utils/src/ft_strtrim.c \
		./utils/src/ft_split.c \
		./utils/src/ft_itoa.c \
		./utils/src/ft_strmapi.c \
		./utils/src/ft_striteri.c \
		./utils/src/ft_putchar_fd.c \
		./utils/src/ft_putstr_fd.c \
		./utils/src/ft_putendl_fd.c \
		./utils/src/ft_putnbr_fd.c \
		./utils/src/ft_lstnew.c \
		./utils/src/ft_lstadd_front.c \
		./utils/src/ft_lstsize.c \
		./utils/src/ft_lstlast.c \
		./utils/src/ft_lstadd_back.c \
		./utils/src/ft_lstdelone.c \
		./utils/src/ft_lstclear.c \
		./utils/src/ft_lstiter.c \
		./utils/src/ft_lstmap.c \
		./utils/src/ft_cleanjoin.c \
		./utils/src/ft_freesplit.c \
		./utils/src/ft_splitlen.c \
		./utils/src/ft_startswith.c \
		./utils/src/ft_endswith.c \
		./utils/src/ft_isequal.c \
		./utils/src/ft_isspace.c \
		./printf/ft_printf.c \
		./printf/src/ft_args_infos.c \
		./printf/src/ft_hexadecimal.c \
		./printf/src/ft_special_ft.c \
		./printf/src/ft_to_pointer.c \
		./printf/src/ft_clear_data.c \
		./printf/src/ft_printf_args.c \
		./printf/src/ft_init_var.c \
		./printf/src/ft_put_args.c \
		./get_next_line/get_next_line.c \
		./get_next_line/get_next_line_utils.c \
		./get_next_line/get_next_line_bonus.c \
		./get_next_line/get_next_line_utils_bonus.c


LIB		= ./utils/libft_utils.h \
		./printf/ft_printf.h \
		libft.h

OBJS	= ${FTS:.c=.o}

OBJSBONUS	= ${FTSBONUS:.c=.o}

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -f

${NAME}:	${OBJS}
		@ar rc ${NAME} ${OBJS}

all:	${NAME}

clean:
		@${RM} ${OBJS} ${OBJSBONUS}

fclean:
		@${RM} ${NAME} ${OBJS} ${OBJSBONUS}

re:
	make fclean all

.PHONY: all clean fclean re
