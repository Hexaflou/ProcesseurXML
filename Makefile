CC = g++
CFLAGS = -Wall
EDL	= g++
LDFLAGS	= -g -DDYDEBUG=1
EXEC_NAME = Xylo
INCLUDES =
LIBS =

all : $(EXEC_NAME)

clean :
	cd AnalyseurXML; make clean
	cd AnalyseurDTD ; make clean
	rm -f $(EXEC_NAME)

objs : 
	cd AnalyseurXML; make objs
	cd AnalyseurDTD; make objs
	$(CC) -o main.o -c main.cpp $(CFLAGS)
	
$(EXEC_NAME) : objs
	$(EDL) -o $(EXEC_NAME) $(wildcard AnalyseurXML/*.o) $(wildcard AnalyseurDTD/*.o) main.o $(LIBS)
