FILES = \
	headers/ft_containers_fox_test/base/foxer_global.cpp \
	headers/ft_containers_fox_test/base/memory_tracker.cpp \
	headers/ft_containers_fox_test/base/statistic_tracker.cpp \
	headers/ft_containers_fox_test/MainTest.cpp \
	main.cpp

OBJ_DIR = _OUT/

OBJ = $(addprefix $(OBJ_DIR), $(FILES:.cpp=.o))
DEPS = $(OBJ:.o=.d)

DEPFLAGS = -MMD -MF $(@:.o=.d)
CFLAGS =  -Wall -Wextra -Werror -I . -std=c++98
#-Wall -Wextra -Werror
NAME = ft_containers

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
