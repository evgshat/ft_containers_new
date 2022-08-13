NAME	= ft_containers
SRCS	= main.cpp
OBJ		= $(SRCS: cpp=.o)
CC		= clang++
FLAGS	= -Wall -Wextra -Werror -std=c++98
RM		= rm -f
HEADERS	= ft_stack.hpp ft_containers.hpp

$(NAME):	$(OBJ)
			$(CC) $(FLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all