#include "genetico.hpp"
#include "dbg.h"


void printar_populacao(Populacao populacao)
{
    std::cout << "{\n";
    for (Cromossomo ind: populacao) {
        std::cout << "\t[\n";
        std::cout << "\t\tDados_GSM = " << ind.qtd_dados_gsm << ",\n";
        std::cout << "\t\tVoz_GSM = " << ind.qtd_voz_gsm << ",\n";
        std::cout << "\t\tDados_WCDMA = " << ind.qtd_dados_wcdma << ",\n";
        std::cout << "\t\tVoz_WCDMA = " << ind.qtd_voz_wcdma << "\n";
        std::cout << "\t]\n";
    }
    std::cout << "}";
}

Cromossomo gerar_cromossomo()
{
    Cromossomo cromossomo;
    cromossomo.qtd_dados_gsm = gerar_usuarios(DADOS_GSM);
    cromossomo.qtd_dados_wcdma = gerar_usuarios(DADOS_WCDMA);
    cromossomo.qtd_voz_gsm = gerar_usuarios(VOZ_GSM);
    cromossomo.qtd_voz_wcdma = gerar_usuarios(VOZ_WCDMA);

    return cromossomo;
}

Populacao gerar_populacao()
{
    Populacao populacao(TAM_POPULACAO);
    for (int i = 0; i < TAM_POPULACAO; i++) {
        populacao[i] = gerar_cromossomo();
    }

    return populacao;
}