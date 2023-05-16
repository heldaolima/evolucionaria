OUT_NAME=main.out

all: genetico binarios
	g++ -o $(OUT_NAME) main.cpp genetico.o binario_utils.o
	clear 

binarios: genetico
	g++ -c binario_utils.cpp

genetico: 
	g++ -c genetico.cpp

clean:
	rm -rf *.o *.out *.gch $(OUT_NAME)