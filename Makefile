CC = gcc

CCFLAGS = -O2 -Wall -pedantic
#CCFLAGS = -g -O0 -v -da -Q
#CCFLAGS = -O2 -pg

LIBS = -lm -lpng

CCP = $(CC) $(CCFLAGS)

BIN = bin
SRC = src

TARGET = terrain
INCLUDE = $(shell find $(SRC) -name *.h)
SOURCE = $(shell find $(SRC) -name *.c)
OBJS = $(SOURCE:.c=.o)

$(TARGET): $(OBJS)
	$(CCP) $(OBJS) -o $(BIN)/$(TARGET) $(LIBS)

%.o: %.c
	$(CCP) -c $< -o $@

all: $(TARGET)

clean:
	rm -f $(TARGET) $(BIN)/$(TARGET) $(SRC)/*.o $(SRC)/*~ $(SRC)/*.c.* *~
