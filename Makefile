CC=g++
CPPFLAGS=-c -Wall -std=c++11 -fmax-errors=4 -fpermissive

all: mainStateMachine

mainStateMachine: main.o astnode.o astbuilder.o expressionparser.o \
	mathexpression.o tokenanalyzer.o
	$(CC) main.o astnode.o astbuilder.o expressionparser.o mathexpression.o \
	tokenanalyzer.o -o mainStateMachine.out

stateMachine: astnode.o astbuilder.o expressionparser.o mathexpression.o \
	tokenanalyzer.o
	$(CC) astnode.o astbuilder.o expressionparser.o mathexpression.o \
	tokenanalyzer.o


main.o:
	$(CC) $(CPPFLAGS) main.cpp
	
astnode.o:
	$(CC) $(CPPFLAGS) astnode.cpp
	
astbuilder.o:
	$(CC) $(CPPFLAGS) astbuilder.cpp
	
expressionparser.o:
	$(CC) $(CPPFLAGS) expressionparser.cpp
	
mathexpression.o:
	$(CC) $(CPPFLAGS) mathexpression.cpp
	
tokenanalyzer.o:
	$(CC) $(CPPFLAGS) tokenanalyzer.cpp
	
clean:
	rm -rf *.o *.hpp.gch mainStateMachine.out
	