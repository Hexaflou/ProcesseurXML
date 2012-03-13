CC=g++
RM = rm
ECHO = @echo
RMFLAGS	= -f
CFLAGS=-c -Wall
LDFLAGS=
SRC=main.cpp
OBJS=$(SOURCES:.cpp=.o)
EXE=Xylo

all: $(SRC) $(EXE)
	
$(EXE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	$(ECHO) nettoyage des binaires translatables
	$(RM) $(RMFLAGS) $(OBJS) core

cleanall: clean
	$(ECHO) nettoyage de l executable
	$(RM) $(RMFLAGS) $(EXE)
