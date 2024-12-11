CC = cc
CFLAGS = -Wall -Wextra -Werror -g
NAME = gnl

SRC_FILES = get_next_line.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(SRC_FILES) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean: 
	rm -f $(OBJ_FILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
