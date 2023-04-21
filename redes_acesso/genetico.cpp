#include "genetico.hpp"
#include "dbg.h"
#include <math.h>
#include <algorithm>

bool order_by_fitness(const Cromossomo &a, const Cromossomo &b)
{
    return a.fitness < b.fitness;
}

void ordenar_populacao(Populacao &populacao)
{
    sort(populacao.begin(), populacao.end(), order_by_fitness);
}

inline double media(Cromossomo c)
{
    double tot = 0.0;

    tot += c.dados_gsm;
    tot += c.voz_gsm;
    tot += c.voz_wcdma;
    tot += c.dados_wcdma;

    return tot / 4.0f;
}

inline double custo_gsm(double dados, double voz)
{
    return std::abs(30 - dados + ((6.0f / 25.0f) * voz));
}

inline double custo_wcdma(double dados, double voz)
{
    return std::abs(80 - dados + ((8.0f / 15.0f) * voz));
}

double fitness(Cromossomo individuo)
{
    double custoGSM = custo_gsm(individuo.dados_gsm, individuo.voz_gsm);
    double custoWCDMA = custo_wcdma(individuo.dados_wcdma, individuo.voz_wcdma);
    double soma_dados = individuo.dados_gsm + individuo.dados_wcdma;
    double soma_voz = individuo.voz_gsm + individuo.voz_wcdma;

    double usuariosDados = 1.0f - (soma_dados / MAX_DADOS);
    double usuariosVoz = 1.0f - (soma_voz / MAX_VOZ);

    return (pow(custoGSM, 2) + pow(custoWCDMA, 2)) * (usuariosDados * usuariosVoz);
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
        populacao[i].media = media(populacao[i]);
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

double proporcao_cromossomo(Cromossomo c)
{
    return (c.dados_gsm + c.dados_wcdma + c.voz_gsm + c.voz_wcdma);
}

double proporcao_populacao(Populacao populacao)
{
    double result = 0.0;
    for (Cromossomo c : populacao)
    {
        result += proporcao_cromossomo(c);
    }
    return result;
}

int escolhido_roleta(Populacao populacao)
{
    int i = 0;
    int escolhido = 0;
    double proporcao = proporcao_populacao(populacao);
    std::vector<double> proporcoes(NUM_SELECIONADOS);
    
    for (i = 0; i < NUM_SELECIONADOS; i++){
        proporcoes[i] = populacao[i].fitness / proporcao;
    }

    double random = random_double();
    for (i = 0; i < NUM_SELECIONADOS; i++) {
        if (proporcoes[i] > random) {
            escolhido = i;
            break;
        } 
    }

    return escolhido;
}

Populacao selecionar(Populacao populacao)
{
    Populacao selecionados(TAM_POPULACAO); // os melhores
    int escolhido = escolhido_roleta(populacao);
    for (int i = 0; i < TAM_POPULACAO; i++)
    {
        selecionados[i] = (i < NUM_SELECIONADOS) ? populacao[i] : populacao[escolhido]; 
    }

    return selecionados;
}