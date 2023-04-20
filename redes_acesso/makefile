OUT_NAME=main.out

all: genetico
	g++ -o $(OUT_NAME) main.cpp genetico.o 

genetico: 
	g++ -c genetico.cpp

clean:
	rm -rf *.o *.out *.gch $(OUT_NAME)