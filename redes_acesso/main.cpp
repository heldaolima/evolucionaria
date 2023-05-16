#include "genetico.hpp"
#include "dbg.h"
#include "binario_utils.hpp"

#define NUM_ITERACOES 1000

Populacao ciclo(Populacao populacao, int iteracao)
{
    int i = 0;
    if (iteracao % 5 == 0) {
        gerar_novos_limites();
        for (i = 0; i < populacao.size(); i++) 
        {
            if (acima_dos_limites(populacao[i])) 
            {
                populacao[i] = gerar_cromossomo();
            }
        }
    }
    Populacao selecionados = selecionar(populacao);
    std::vector<std::string> selecionados_binarios = populacao_to_binario(selecionados);
    cruzamento(selecionados_binarios);
    for (i = 1; i < TAM_POPULACAO; i++) {
        mutacao(selecionados_binarios[i]);
    }
    populacao = decodificar_populacao(selecionados_binarios);
    printar_populacao(populacao);
    // print_limites();

    return populacao;
}

int main(int argc, char* argv[])
{
    seed();
    
    int i = 1;
    Populacao populacao = gerar_populacao();
    ordenar_populacao(populacao);
    while (i <= NUM_ITERACOES) {
        populacao = ciclo(populacao, i);
        ++i;
    }
    restaurar_limites();

    return 0;
}