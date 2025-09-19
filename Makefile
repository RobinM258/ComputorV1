NAME = Converter

F = main 

S = $(foreach f, $(F), $(f).cpp)
OBJ = $(S:.cpp=.o)
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJ)
	@c++ $(OBJ) $(CFLAGS) -o $(NAME)

.cpp.o:
	@c++ -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all