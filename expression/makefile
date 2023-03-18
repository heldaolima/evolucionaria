all: expression grammar
	g++ -o expression_prob main.cpp expression.o grammar.o

expression: grammar
	g++ -c expression.cpp

grammar:
	g++ -c grammar.cpp

clear:
	rm -rf *.o *.out *.gch