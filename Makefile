##
## EPITECH PROJECT, 2018
## cpp_rush2
## File description:
## Makefile
##

ECHO		=	/bin/echo -e
DEFAULT		=	"\033[00m"
GREEN		=	"\033[0;32m"
TEAL		=	"\033[1;36m"
RED		=	"\033[0;31m"

SRCS		=	Srcs/Parser/Parser.cpp			\
			Srcs/Factory/ComponentFactory.cpp	\
			Srcs/Validator/Validator.cpp		\
			Srcs/Circuit/Circuit.cpp		\
			Srcs/Invite/Invite.cpp			\
			Srcs/Error/Error.cpp			\
			Srcs/TruthTable/TruthTable.cpp		\
			Srcs/Components/Input.cpp		\
			Srcs/Components/Output.cpp		\
			Srcs/Components/True.cpp		\
			Srcs/Components/False.cpp		\
			Srcs/Components/Comp4081.cpp		\
			Srcs/Components/Comp4071.cpp		\
			Srcs/Components/Comp4011.cpp		\
			Srcs/Components/Comp4001.cpp		\
			Srcs/Components/Comp4030.cpp		\
			Srcs/Components/Comp4069.cpp		\
			Srcs/main.cpp

OBJS		=	$(SRCS:.cpp=.o)

NAME		=	nanotekspice

CPPFLAGS	+= 	-std=c++11 -W -Wall -Wextra -IInc/

CC		=	g++

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean debug re

.cpp.o:
		@g++ $(CPPFLAGS) -c $< -o $@ && \
		$(ECHO) $(GREEN) "[ OK ]" $(TEAL) $< $(DEFAULT) || \
		$(ECHO) $(RED) "[ XX ]" $(TEAL) $< $(DEFAULT)
