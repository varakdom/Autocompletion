##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Compilation Makefile for printf
##

SRC =	src/main.cpp 	\
		src/Address.cpp 	\
		src/Choice.cpp 	\
		src/Dictionnaire.cpp 	\
		src/Street.cpp \

OBJ = 	$(SRC:.cpp=.o)

%.o: %.cpp
	g++ $< -c -o $@ $(DEBUGFLAGS)

CFLAGSMAC += -std=c++20 -Wall -Wextra -Werror

CFLAGS += -Wall -Wextra -Werror

DEBUGFLAGS = 

NAME =  autoCompletion

all:	$(NAME)

$(NAME): $(OBJ)
		g++ $(CFLAGS) -o $(NAME) $(OBJ) $(DEBUGFLAGS)

$(NAMEMAC): $(OBJ)
		g++ $(CFLAGSMAC) -o $(NAME) $(OBJ)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: 	fclean all

mac: $(NAMEMAC)

debug:
	make re "DEBUGFLAGS=-fsanitize=address -g -ggdb3"