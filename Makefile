include colors.mk

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -I /goinfre/$$USER/.brew/opt/readline/include
#-L $(brew --prefix readline)/lib -I $(bash brew --prefix readline)/include#
FSANITIZE = -fsanitize=address -g

SRCSDIR = ./srcs/
SRCSCFILES = minishell.c signal.c utils.c utils2.c utils_free.c

BINDIR = ${addprefix ${SRCSDIR}, builtins/}
BINCFILES = ft_export.c ft_unset.c ft_pwd.c ft_cd.c ft_echo.c ft_env.c ft_exit.c builtin_utils.c

BINDIR = ${addprefix ${SRCSDIR}, builtins/}
BINCFILES = ft_export.c ft_unset.c ft_pwd.c ft_cd.c ft_echo.c ft_env.c ft_exit.c builtin_utils.c

ENVDIR = ${addprefix ${SRCSDIR}, env/}
ENVCFILES = env.c env_utils.c env_utils_doble.c env_utils_find.c env_utils_find2.c env_replace.c shlevel.c

LEXDIR = ${addprefix ${SRCSDIR}, lexer/}
LEXCFILES = lexer.c lexer_utils.c char_handler.c

PARSEDIR = ${addprefix ${SRCSDIR}, parser/}
PARSECFILES = parser.c create_ast.c

EXECDIR = ${addprefix ${SRCSDIR}, executor/}
EXECCFILES = execute.c path.c heredocs.c redir.c path_utils.c utils.c

ERRDIR = ${addprefix ${SRCSDIR}, errors/}
ERRFILES = error_msg.c syntax_errors.c

SRCS =	${addprefix ${SRCSDIR}, ${SRCSCFILES}} \
		${addprefix ${BINDIR}, ${BINCFILES}} \
		${addprefix ${ENVDIR}, ${ENVCFILES}} \
		${addprefix ${LEXDIR}, ${LEXCFILES}} \
		${addprefix ${PARSEDIR}, ${PARSECFILES}} \
		${addprefix ${EXECDIR}, ${EXECCFILES}} \
		${addprefix ${ERRDIR}, ${ERRFILES}}

OBJS = ${SRCS:.c=.o}

LFT_NAME = libft.a
LIB_DIR = ./libft/

INC = -I ./includes/ -I ${LIB_DIR}includes/
LDLIBS = -L /goinfre/$$USER/.brew/opt/readline/lib  -lreadline

LDLIBS += -L${LIB_DIR} -lft ${READLINE}

RM = rm -rf
################################################################################
.PHONY: all re fclean clean test setup
################################################################################
all: ${NAME}

test: ${NAME}
	./${NAME}

retest: re
	./${NAME}

${NAME}: ${OBJS}
	@make -s -C ${LIB_DIR}
	@printf "\n${God}${Green}Created 'libft.a'.${NoColor}\n"
	@${CC}  ${CFLAGS} ${OBJS} ${LDLIBS} -o ${NAME}
	@printf "${God} ${BIBlue}Mini${NoColor}🐚 de ${BIPurple}LaLora${NoColor}${God}\n"

${LFT_NAME}:
	@make -s -C ${LIB_DIR}

%.o: %.c
	@${CC} -c ${CFLAGS} $^ -o $@ ${INC}
	@printf "${BIGreen}[Compiled]${BIBlue} $^ ${NoColor}to ${BIPurple}$@ ${NoColor}                       \r"

re: fclean all

clean:
	@make -s -C ${LIB_DIR} clean
	@${RM} ${OBJS}
	@printf "${Bad}${BIRed}Delete *.o${NoColor}${Bad}\n"

fclean: clean
	@make -s -C ${LIB_DIR} fclean
	@${RM} ${NAME}
	@printf "${Bad}${BIRed}Delete ${NAME}${NoColor}${Bad}\n"


setup:
	@rm -rf $$HOME/.brew && git clone https://github.com/Homebrew/brew $$HOME/goinfre/.brew
	#echo 'export PATH=$$HOME/goinfre/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc
	@brew update
	@brew install readline
	@printf "${God}${BICyan}Install brew and library in MAC.${God}${NoColor}"
################################################################################
