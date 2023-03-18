OUT_NAME=main.out

all: expression grammar
	g++ -o $(OUT_NAME) main.cpp expression.o grammar.o

expression: grammar
	g++ -c expression.cpp

grammar:
	g++ -c grammar.cpp

clean:
	rm -rf *.o *.out *.gch $(OUT_NAME)