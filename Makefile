CC     = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
TARGET = cricket

all: $(TARGET)

$(TARGET): cricket.c
	$(CC) $(CFLAGS) -o $(TARGET) cricket.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
