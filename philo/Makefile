NAME 		= 	philo

SRC 		= 	philo.c \
				parsing.c \
				errors.c \
				init.c \
				routines.c \
				dinning_table.c \
				time.c \
				checkup.c \
				utils.c \
				helpers/ft_atoi.c helpers/ft_split.c helpers/ft_strlen.c \

OBJ = $(SRC:.c=.o)

CC = cc 
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lpthread

REM		=	rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
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