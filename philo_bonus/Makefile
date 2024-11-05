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
# LDFLAGS = -lpthread

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

tsan: CFLAGS += -fsanitize=thread,undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds -g3 -O3 -fno-omit-frame-pointer
tsan: re

# asan: CFLAGS += -fsanitize=address,undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds -g3 -O3 -fno-omit-frame-pointer
# asan: re

.PHONY: all clean fclean re bonus