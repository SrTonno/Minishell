include colors.mk
###############################################################################
#                                              FILES                          #
###############################################################################
CFILES		= \
			prueba.c
OBJS	=	${CFILES:.c=.o}

###############################################################################
#                                              SETTINGS                       #
###############################################################################
NAME = minishell
HDRS = philo.h

NLIBRARY= libft.a

CC = gcc
CFLAGS = -Wall -Werror -Wextra
READLINE = -lreadline $$LDFLAGS  $$CPPFLAGS= # -L $$HOME/goinfre/.brew/opt/readline/lib -I $$HOME/goinfre/.brew/opt/readline/include
OPGRAFIC = -lmlx -framework OpenGL -framework AppKit
FSANITIZE = -fsanitize=address -g

AR = ar
ARFLAGS = -rcs
RM = rm -f

LIBFT = $(OLIBFT) $(OPRINTF) $(OGNL)

###############################################################################
#                                              OPTIONS                        #
###############################################################################
all: ${NAME}

${NAME}:  ${OBJS}
	@${CC} ${CFLAGS} ${READLINE} ${OBJS} -o $@
	@echo "${God}${Green}Created '${NAME}'.${NoColor}"

git: fclean
	@echo "\t${BIPurple}>>Push To Git<<${NoColor}"
	@git remote -v | cut -d " " -f 1 | uniq
	@git add . ;
	@read -p "Name the commit: " commit ;\
	git commit -m "$$commit" ;\
	read -p "Check the files..." -t 20;
	@git push origin master ;

normi:
	@echo "${BICyan}>>Check Files with ${BIRed}ERROR${BICyan} norminette<<${NoColor}"
	@norminette -R CheckForbiddenSourceHeader | grep Error! | grep -v tester
	@echo "Total Errores $$(norminette -R CheckForbiddenSourceHeader | grep -v Error! | grep -v tester | wc -l)"

staup:
	rm -rf $$HOME/.brew && git clone https://github.com/Homebrew/brew $$HOME/goinfre/.brew
	echo 'export PATH=$$HOME/goinfre/.brew/bin:$$PATH' >> $$HOME/.zshrc && source $$HOME/.zshrc
	brew update
	brew install readline
	@echo "${God}${Purple}Install brew and library in MAC.${NoColor}"

.c.o:
		@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

###############################################################################
clean:
		@${RM} ${OBJS}
		@echo "${Bad}${Red}Delete .o.${NoColor}"

fclean: clean
		@${RM} ${NAME}
		@echo "${Bad}${Red}Delete '${NAME}'.${NoColor}"


re: fclean all

help:
	@echo "${UGreen}Options of MakeFile:${NoColor}"
	@echo "Used: make [options]"
	@echo "\t${BICyan}Default:${NoColor} Created '${NAME}'"
	@echo "\t${IRed}clean:${NoColor} Delete '.o'."
	@echo "\t${BIRed}fclean:${NoColor} Delete'.o', '${NLIBRARY}'"
	@echo "\t${BICyan}re:${NoColor} Delete '.o', '${NLIBRARY}', '${NAME}' and creates '${NAME}'"
	@echo "\t${BIPurple}git:${NoColor} Push to git."
	@echo "\t${BICyan}normi:${NoColor} Check file with Error the norminette."
	@echo "MakeFile by ${UBlue}tvillare${NoColor}."

.PHONY = all clean fclean re help normi git
