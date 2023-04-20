#include "genetico.hpp"
#include "dbg.h"

int main(int argc, char* argv[])
{
    seed();

    // Populacao populacao = gerar_populacao();
    // printar_populacao(populacao);

    Cromossomo teste;
    teste.dados_gsm = 24.96;
    teste.voz_gsm = 50;
    teste.dados_wcdma = 36;
    teste.voz_wcdma = 82.50;

    debug("fitness=%lf", fitness(teste));
    
    return 0;
}