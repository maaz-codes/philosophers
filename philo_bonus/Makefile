NAME 		= 	philo_bonus

SRC 		= 	philo_bonus.c \
				parsing_bonus.c \
				errors_bonus.c \
				init_bonus.c \
				time_bonus.c \
				routines_bonus.c \
				utils.c \
				dinning.c \
				semaphores.c \
				helpers/ft_atoi.c helpers/ft_split.c helpers/ft_strlen.c \

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

REM		=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@
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