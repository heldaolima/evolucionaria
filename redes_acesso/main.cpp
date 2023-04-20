#include "genetico.hpp"

int main(int argc, char* argv[])
{
    seed();
    
    Populacao populacao = gerar_populacao();
    printar_populacao(populacao);
    
    return 0;
}