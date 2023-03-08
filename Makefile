include colors.mk

NAME = minishell

CC = gcc
# CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I /goinfre/$$USER/.brew/opt/readline/include
#-L $(brew --prefix readline)/lib -I $(bash brew --prefix readline)/include#


SRCSDIR = ./srcs/
SRCSCFILES = minishell.c signal.c utils.c

BINDIR = ${addprefix ${SRCSDIR}, bin/}
BINCFILES = 

LEXDIR = ${addprefix ${SRCSDIR}, lexer/}
LEXCFILES = lexer.c lexer_utils.c char_handler.c

PARSEDIR = ${addprefix ${SRCSDIR}, parser/}
PARSECFILES = 

EXECDIR = ${addprefix ${SRCSDIR}, executor/}
EXECCFILES = 

SRCS =	${addprefix ${SRCSDIR}, ${SRCSCFILES}} \
		${addprefix ${BINDIR}, ${BINCFILES}} \
		${addprefix ${LEXDIR}, ${LEXCFILES}} \
		${addprefix ${PARSEDIR}, ${PARSECFILES}} \
		${addprefix ${EXECDIR}, ${EXECCFILES}}

OBJS = ${SRCS:.c=.o}

LFT_NAME = libft.a
LIB_DIR = ./libft/

INC = -I ./includes/ -I ${LIB_DIR}includes/
LDLIBS =  -L /goinfre/$$USER/.brew/opt/readline/lib  -lreadline

LDLIBS += -L${LIB_DIR} -lft ${READLINE}

RM = rm -rf
################################################################################
.PHONY: all re fclean clean
################################################################################
all: ${NAME}

test: ${NAME}
	./${NAME}

${NAME}: ${LFT_NAME} ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} ${LDLIBS} -o ${NAME}

${LFT_NAME}:
	@make -s -C ${LIB_DIR}

%.o: %.c
	@${CC} -c ${CFLAGS} $^ -o $@ ${INC}

re: fclean all

clean:
	@make -s -C ${LIB_DIR} clean
	@${RM} ${OBJS}

fclean: clean
	@make -s -C ${LIB_DIR} fclean
	@${RM} ${NAME}

staup:
	rm -rf $$HOME/.brew && git clone https://github.com/Homebrew/brew $$HOME/goinfre/.brew
	#echo 'export PATH=$$HOME/goinfre/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc
	brew update
	brew install readline
	@echo "Install brew and library in MAC."

################################################################################
