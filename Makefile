NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCSDIR = ./srcs/
SRCSCFILES = minishell.c

BINDIR = ${addprefix ${SRCSDIR}, bin/}
BINCFILES = 

SCANDIR = ${addprefix ${SRCSDIR}, scanner/}
SCANCFILES = 

PARSEDIR = ${addprefix ${SRCSDIR}, parser/}
PARSECFILES = 

EXECDIR = ${addprefix ${SRCSDIR}, executor/}
EXECCFILES = 

SRCS =	${addprefix ${SRCSDIR}, ${SRCSCFILES}} \
		${addprefix ${BINDIR}, ${BINCFILES}} \
		${addprefix ${SCANDIR}, ${SCANCFILES}} \
		${addprefix ${PARSEDIR}, ${PARSECFILES}} \
		${addprefix ${EXECDIR}, ${EXECCFILES}}

OBJS = ${SRCS:.c=.o}

LIB = libft.a
LIBDIR = ./libft/

INC = -I ./includes/ -I ${LIBDIR}includes/

LIBRARIES = -L${LIBDIR} -lft -lreadline

RM = rm -rf
################################################################################
.PHONY: all re fclean clean
################################################################################
all:		${NAME}

test:		${NAME}
		./${NAME}

${NAME}:	${OBJS}
		@make -s ${LIB}
		${CC} $^ ${LIBRARIES} -o ${NAME}

${LIB}:
		@make -s -C ${LIBDIR}

%.o:		%.c
		${CC} -c ${CFLAGS} $^ -o $@ ${INC}

re:			fclean all

fclean:		clean
		@make -s -C ${LIBDIR} fclean
		@${RM} ${NAME}

clean:
		@make -s -C ${LIBDIR} clean
		@${RM} ${OBJS}
################################################################################
