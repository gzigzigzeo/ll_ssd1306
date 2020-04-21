CC = gcc
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CFLAGS = -W -Wall -I .

ll_ssd1306_test: ll_ssd1306_test.o ll_ssd1306.o

test: ll_ssd1306_test
	./ll_ssd1306_test

clean:
	rm -f $(OBJ)
