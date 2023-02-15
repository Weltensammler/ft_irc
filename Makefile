CC			= c++
CFLAGS		= -Wall -Werror -Wextra -std=c++98 #-g -Og
RM			= rm -f
NAME		= irc

SRC			= main.cpp

OBJ			= $(SRC:cpp=o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(OBJ) $(CFLAGS) -o $(NAME)

clean:
			$(RM) $(OBJ)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re