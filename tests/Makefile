CC=g++
CPPFLAGS=-Wall -std=c++11 -fmax-errors=4 -fpermissive

all: testMathExpr

testMathExpr:
	$(CC) $(CPPFLAGS) testmathexpression.cpp \
	../astbuilder.cpp ../astnode.cpp ../expressionparser.cpp \
	../mathexpression.cpp ../tokenanalyzer.cpp -o tmathexpr.out
	
clean:
	rm -rf *.o