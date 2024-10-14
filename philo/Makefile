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
				libft/ft_atoi.c libft/ft_split.c libft/ft_strjoin.c libft/ft_strlen.c libft/ft_strncmp.c \

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -g3 -O3 # -Wall -Wextra
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

tsan: CFLAGS += -fsanitize=thread,undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds -g3 -O3 -fno-omit-frame-pointer
tsan: re

asan: CFLAGS += -fsanitize=address,undefined,float-divide-by-zero,unsigned-integer-overflow,implicit-conversion,local-bounds -g3 -O3 -fno-omit-frame-pointer
asan: re

.PHONY: all clean fclean re bonus