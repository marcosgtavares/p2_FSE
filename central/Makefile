EXEC = P2_CENTRAL
CXX = gcc             
OPTS = -O2 -Wall -g   
CFLAGS = $(OPTS)      
LDFLAGS = -lpthread -lncurses        


INCDIR = inc
OBJDIR = obj
BINDIR = bin
SRCDIR = src


CFLAGS += -I$(INCDIR) -I$(SRCDIR)


SOURCES = alarm_controler.c client.c csv_gen.c main.c server.c w_interface.c


_OBJ = $(SOURCES:.c=.o)
OBJ = $(patsubst %,$(OBJDIR)/%,$(_OBJ))

all: $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC): $(OBJ)
		$(CXX) -o $(BINDIR)/$(EXEC) $(OBJ) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		$(CXX) -c -o $@ $< $(CFLAGS)

clean:
		rm -vf $(BINDIR)/$(EXEC) $(OBJ)

./bin/P2_CENTRAL