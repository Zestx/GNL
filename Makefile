CC=gcc
CFLAGS=-Wall -Wextra -Werror --pedantic

all: lib
	$(CC) $(CFLAGS) -g -o  gnl.o -c get_next_line.c
	$(CC) $(CFLAGS) -g -o  main.o -c main.c
	$(CC) -g -o test_gnl main.o gnl.o -I libft -L libft/ -lft


lib:
	make -C libft/ fclean && make -C libft/

clean:
	rm *.o

fclean: clean
	rm test_gnl
