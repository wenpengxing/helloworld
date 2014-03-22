CC=gcc
CFLAGS:=-c -Wall
CPPFLAGS:=-I./
SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))
TARGET=libstack.a

$(TARGET):$(OBJ)
	ar rs $@ $^
%.o:%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $<

.PHONY:clean
clean:
	-rm -f $(OBJ)
	-rm -f $(TARGET)
test:
	@echo $(SRC)
	@echo $(OBJ)
