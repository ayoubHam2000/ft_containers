FILES = \
	src/Vector.cpp \
	main.cpp

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.cpp=.o))
DEPS = $(OBJ:.o=.d)

DEPFLAGS = -MMD -MF $(@:.o=.d)
CFLAGS =  -I ./headers -std=c++98 -g
#-Wall -Wextra -Werror
NAME = containers

all: $(NAME)

$(NAME): $(OBJ)
	c++ $(OBJ) -o $(NAME)

$(OBJ): $(OBJ_DIR)%.o:%.cpp
	@mkdir -p $(dir $@)
	c++ $(CFLAGS) -c $(@:$(OBJ_DIR)%.o=%.cpp) $(DEPFLAGS) -o $(@)

-include $(DEPS)

clean:
	rm -rf _OUT

fclean: clean
	rm -f $(NAME)

re: fclean all
