#include "genetico.hpp"
#include "dbg.h"


int main(int argc, char* argv[])
{
    seed();

    Populacao populacao = gerar_populacao();
    ordenar_populacao(populacao);
    // printar_populacao(populacao);
    populacao = selecionar(populacao);
    std::vector<std::string> test = {"ads"};
    mutacao(test);
    
    return 0;
}