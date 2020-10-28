CC				= g++
CFLAGS		= -std=c++11
LDFLAGS 	= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
TARGET 		= main
OBJFILES	= main.o ChessPiece.o Board.o 

# all: $(TARGET)

$(TARGET): $(objects)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJFILES)
