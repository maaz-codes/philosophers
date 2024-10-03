NAME 		= 	philo

SRC 		= 	philo.c \
				parsing.c \
				errors.c \
				init.c \
				routines.c \
				dinning_table.c \
				libft/ft_atoi.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strncmp.c \

OBJ = $(SRC:.c=.o)

CC = cc
# CFLAGS = -Wall -Wextra -Werror
REM		=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@cc $(CFLAGS) $^ -o $@
	@echo "\033[1;36m Table's Prepared🍽 \033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@$(REM) $(OBJ)
	@echo "\033[1;36m Table's Cleaned✨ \033[0m"
fclean: clean
	@$(REM) $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
