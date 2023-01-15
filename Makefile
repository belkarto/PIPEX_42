#----------------------------------------------#
# 					Colors
#----------------------------------------------#
NO_COLOR    = \033[0m
GRAY 		= \033[0;90m
RED 		= \033[1:4;5;91m
GREEN 		= \033[1;3;5;92m
#----------------------------------------------#
NAME		= pipex
CFLAGS		= -Wall -Wextra -Werror 
#-g -fsanitize=address
SRC			= main.c pipex_utils.c
OBJEC		= $(SRC:.c=.o)
LIBFT		= my_lib/libft.a


all			: $(NAME)

%.o			: %.c
	@printf "\r$(GRAY)making objects...$(NO_COLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@


$(NAME)		: $(LIBFT) $(OBJEC) 
	@printf "\r$(GREEN) -->DONE<--$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(OBJEC) my_lib/libft.a -o $(NAME)


$(LIBFT)	:
	@make -C my_lib

clean		:
	@make clean -C my_lib
	@rm -f $(OBJEC) 
	@printf "\r$(RED)--> cleaned <--\n$(NO_COLOR)"

fclean		: clean
	@make fclean -C my_lib
	@rm -f $(NAME) 	
	@printf "\r$(RED)--> cleaned <--\n$(NO_COLOR)"

re			: fclean all

.PHONY		: all clean fclean bonus re

