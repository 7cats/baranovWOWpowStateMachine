CC=g++
CPPFLAGS=-c -Wall -std=c++11 -fmax-errors=4

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
	$(CC) $(CPPFLAGS) astnode.cpp astnode.hpp
	
astbuilder.o:
	$(CC) $(CPPFLAGS) astbuilder.cpp astbuilder.hpp
	
expressionparser.o:
	$(CC) $(CPPFLAGS) expressionparser.cpp expressionparser.hpp
	
mathexpression.o:
	$(CC) $(CPPFLAGS) mathexpression.cpp mathexpression.hpp
	
tokenanalyzer.o:
	$(CC) $(CPPFLAGS) tokenanalyzer.cpp tokenanalyzer.hpp
	
clean:
	rm -rf *.o *.hpp.gch mainStateMachine.out
	