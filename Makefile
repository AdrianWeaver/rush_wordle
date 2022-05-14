NAME = wordle

#############################################################################
#							COMPILER										#
#############################################################################
				
CC = c++

CFLAGS = -MMD -g3 -Wall -Wextra

INC = -I ./includes

#############################################################################
#							PATHS											#
#############################################################################

SRCS_PATH = ./sources/

OBJS_PATH = ./objects/

#############################################################################
#							FILES											#
#############################################################################

SRCS = main.cpp

OBJS = $(addprefix $(OBJS_PATH), $(SRCS:.cpp=.o))

DEPS = $(OBJS:.o=.d)

#############################################################################
#							RULES											#
#############################################################################

all:	$(NAME)

$(NAME):	$(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJS_PATH)%.o:	$(SRCS_PATH)%.cpp
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
			@rm -rf $(OBJS_PATH)
			@echo "Objs cleaned!"

fclean:		clean
			@rm -f $(NAME)
			@echo "Executable file cleaned"

re:			fclean
			$(MAKE) all

test:		$(NAME)
			./$(NAME)

-include $(DEPS)
.PHONY:		all clean fclean re test
