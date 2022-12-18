NAME = containers

CC = c++

FLAGS = -Wall -Werror -Wextra -std=c++98

OBJ = $(SRC:.cpp=.o)

STL_OBJ = $(STD_SRC:.cpp=.o)

SRC =	main.cpp

LIB =	vector.hpp\
		stack.hpp\
		map.hpp\
		set.hpp\
		iterators.hpp\
		type_enable.hpp\
		extra_algos.hpp\
		pair.hpp\
		redBlackTree.hpp\

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME)

%.o : %.cpp $(LIB)
	$(CC) $(FLAGS) -o $@ -c $<

clean :
	rm -f $(OBJ) $(STL_OBJ)

fclean : clean
	rm -f $(NAME) $(STD_NAME) a.out

re : fclean all