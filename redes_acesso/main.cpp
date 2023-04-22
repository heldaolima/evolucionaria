#include "genetico.hpp"
#include "dbg.h"
#include "binario_utils.hpp"

#define NUM_ITERACOES 50

Populacao ciclo(Populacao populacao)
{
    Populacao selecionados = selecionar(populacao);
    std::vector<std::string> selecionados_binarios = populacao_to_binario(selecionados);
    cruzamento(selecionados_binarios);
    for (int i = 1; i < TAM_POPULACAO; i++) {
        mutacao(selecionados_binarios[i]);
    }
    populacao = decodificar_populacao(selecionados_binarios);
    printar_populacao(populacao);

    return populacao;
}

int main(int argc, char* argv[])
{
    seed();

    int i = 0;
    Populacao populacao = gerar_populacao();
    ordenar_populacao(populacao);
    while (i < NUM_ITERACOES) {
        populacao = ciclo(populacao);
        ++i;
    }
    
    return 0;
}