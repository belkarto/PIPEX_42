#----------------------------------------------#
# 					Colors
#----------------------------------------------#
NO_COLOR    = \033[0m
GRAY 		= \033[0;90m
RED 		= \033[1:4;5;91m
GREEN 		= \033[1;3;5;92m
#----------------------------------------------#
NAME		= pipex
B_NAME		= pipex_bonus
CFLAGS		= -Wall -Wextra -Werror 
#-g -fsanitize=address
SRC			= src/main.c src/pipex_utils.c src/pipex_utils2.c
B_SRC		= bonus_src/main_bonus.c bonus_src/pipex_utils_bonus.c \
			  bonus_src/pipex_utils_bonus2.c
OBJEC		= $(SRC:.c=.o)
B_OBJECT	= $(B_SRC:.c=.o)
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

bonus		: $(B_NAME)

$(B_NAME)	: $(LIBFT) $(B_OBJECT)
	@printf "\r$(GREEN) -->DONE<--$(NO_COLOR)"
	@$(CC) $(CFLAGS) $(B_OBJECT) my_lib/libft.a -o $(B_NAME)

clean		:
	@make clean -C my_lib
	@rm -f $(OBJEC) $(B_OBJECT)
	@printf "\r$(RED)--> cleaned <--\n$(NO_COLOR)"

fclean		: clean
	@make fclean -C my_lib
	@rm -f $(NAME) $(B_NAME)
	@printf "\r$(RED)--> cleaned <--\n$(NO_COLOR)"

re			: fclean all

.PHONY		: all clean fclean bonus re

