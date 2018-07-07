NAME := fillit

SRC = fillit.c solver.c map.c parse.c place.c

FLAGS := -Wall -Werror -Wextra

INCLUDES := -I. -I./libft/

LIBS := -Llibft/ -lft

all : $(NAME)

$(NAME) : $(SRC) ./fillit.h
	make -C libft/
	gcc $(FLAGS) $(INCLUDES) $(LIBS) $(SRC) -o $(NAME)

clean :
	rm -rf $(NAME)

fclean : clean
	make -C libft/ fclean
	rm -rf $(SRC:.c=.o)

re : fclean all

ez :
	rm -rf $(NAME)
	gcc $(INCLUDES) $(LIBS) $(SRC) -o $(NAME)

.PHONY = $(NAME) all clean fclean re
