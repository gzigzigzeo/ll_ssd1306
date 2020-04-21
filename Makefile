CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

ll_ssd1306_test: ll_ssd1306_test.o ll_ssd1306.o

clean:
	rm -f $(OBJ)
