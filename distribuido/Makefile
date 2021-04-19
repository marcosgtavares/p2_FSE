EXEC = P2_DISTRIBUIDO
CXX = gcc             
OPTS = -O2 -Wall -g   
CFLAGS = $(OPTS)      
LDFLAGS = -lpthread -lncurses        


INCDIR = inc
OBJDIR = obj
BINDIR = bin
SRCDIR = src


CFLAGS += -I$(INCDIR) -I$(SRCDIR)


SOURCES = bme280_i2c.c bme280.c client.c gpio.c main.c server.c


_OBJ = $(SOURCES:.c=.o)
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJ)
		$(CXX) -o $(BINDIR)/$(EXEC) $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		$(CXX) -c -o $@ $< $(CFLAGS)

clean:
		rm -vf $(BINDIR)/$(EXEC) $(OBJ)

run:
		./bin/P2_DISTRIBUIDO