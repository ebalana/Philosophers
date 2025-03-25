# Colors
DEF_COLOR = \033[0;39m
GREEN = \033[0;92m
RED = \033[0;91m

# Source files
SRCS =	src/main.c \
		src/check.c \
		src/free.c \
		src/init_data.c \
		src/philo_life.c \

# Object files
OBJS = ${SRCS:.c=.o}

# Target binary name
NAME = philo
CC = cc
CFLAGS = -Wall -Werror -Wextra -lpthread -g -fsanitize=address
RM = rm -f

HEADER = include/philo.h

# Build everything
all: $(NAME)

# Compile .c to .o
.c.o:
	${CC} ${CFLAGS} -c $< -o $@

# Build the program
$(NAME): $(OBJS) Makefile $(HEADER)
	${CC} ${CFLAGS} $(OBJS) -o ${NAME}
	@echo "$(GREEN)Project compiled!$(DEF_COLOR)"

# Clean objects
clean:
	${RM} ${OBJS}
	@echo "$(RED)Cleaned object files$(DEF_COLOR)"

# Clean all files
fclean: clean
	${RM} ${NAME}
	@echo "$(RED)Cleaned all binaries$(DEF_COLOR)"

# Rebuild project
re: fclean all

.PHONY: all clean fclean re