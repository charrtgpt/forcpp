NAME = PmergeMe

SRC_FLS = main.cpp PmergeMe.cpp

FLAGS = -Wall -Wextra -Werror -std=c++98

CPP = c++

HEADER = PmergeMe.hpp

OBJ_FLS = $(SRC_FLS:.cpp=.o)

$(NAME): $(OBJ_FLS)
	$(CPP)  $(FLAGS) $(OBJ_FLS) -o $@

all: $(NAME)

%.o: %.cpp $(HEADER)
	$(CPP) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FLS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: clean fclean all re

.SECONDARY:%         