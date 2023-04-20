#include "genetico.hpp"
#include "dbg.h"
#include <math.h>

inline double custo_gsm(double dados, double voz) 
{
    return std::abs(30 - dados + ((6.0f/25.0f) * voz));
}

inline double custo_wcdma(double dados, double voz)
{
    return std::abs(80 - dados + ((8.0f/15.0f) * voz));
}

double fitness(Cromossomo individuo)
{
    double custoGSM = custo_gsm(individuo.dados_gsm, individuo.voz_gsm);
    double custoWCDMA = custo_wcdma(individuo.dados_wcdma, individuo.voz_wcdma);
    double soma_dados = individuo.dados_gsm + individuo.dados_wcdma;
    double soma_voz = individuo.voz_gsm + individuo.voz_wcdma;

    debug("soma_dados=%lf soma_voz=%lf", soma_dados, soma_voz);
    debug("max_dados=%lf max_voz=%lf\n", MAX_DADOS, MAX_VOZ);

    double usuariosDados = 1.0f - (soma_dados / MAX_DADOS);
    double usuariosVoz = 1.0f - (soma_voz / MAX_VOZ);


    debug("custoGSM=%lf custoWCDMA=%lf usuariosDados=%lf usuariosVoz=%lf",
        custoGSM, custoWCDMA, usuariosDados, usuariosVoz); 

    return ((pow(custoGSM, 2) + pow(custoWCDMA, 2)) * usuariosDados * usuariosVoz);
}

Cromossomo gerar_cromossomo()
{
    Cromossomo cromossomo;
    cromossomo.dados_gsm = gerar_usuarios(DADOS_GSM);
    cromossomo.dados_wcdma = gerar_usuarios(DADOS_WCDMA);
    cromossomo.voz_gsm = gerar_usuarios(VOZ_GSM);
    cromossomo.voz_wcdma = gerar_usuarios(VOZ_WCDMA);

    return cromossomo;
}

Populacao gerar_populacao()
{
    Populacao populacao(TAM_POPULACAO);
    for (int i = 0; i < TAM_POPULACAO; i++)
    {
        populacao[i] = gerar_cromossomo();
        populacao[i].fitness = fitness(populacao[i]);
    }

    return populacao;
}

void printar_populacao(Populacao populacao)
{
    std::cout << "{\n";
    for (Cromossomo ind : populacao)
    {
        std::cout << "\t[\n";
        std::cout << "\t\tDados_GSM = " << ind.dados_gsm << ",\n";
        std::cout << "\t\tVoz_GSM = " << ind.voz_gsm << ",\n";
        std::cout << "\t\tDados_WCDMA = " << ind.dados_wcdma << ",\n";
        std::cout << "\t\tVoz_WCDMA = " << ind.voz_wcdma << ",\n";
        std::cout << "\t\tFITNESS = " << ind.fitness << "\n";
        std::cout << "\t]\n";
    }
    std::cout << "}";
}