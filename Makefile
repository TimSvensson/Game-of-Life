CC		=gcc
CFLAGS	=-Wall -std=c99

ODIR	=./obj
SDIR	=./src
IDIR	=./inc

DEPS	= $(IDIR)/gol_00.h

_OBJ	= gol_00.o
OBJ		= $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game-of-life: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(ODIR)/*.o
	rm -f game-of-life.exe