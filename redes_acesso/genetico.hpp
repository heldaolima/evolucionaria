#ifndef _genetico_hpp
#define _genetico_hpp

#include "dbg.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>

#define seed() (srand((unsigned)time(NULL)))
#define randint(n) (rand() % n)
#define randint_interval(i, n) (i + randint(n))
#define print_vec(V) \
    for (auto n : V) \
        std::cout << n << " ";
#define random_double() (rand() / static_cast<double>(RAND_MAX))

inline double randfrom(double min, double max) 
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

#define TAM_POPULACAO 4
#define PROB_MUTACAO 0.2f
#define PROB_ELITE 0.5f

#define NUM_SELECIONADOS ((int) (PROB_ELITE*TAM_POPULACAO))

#define QTD_BITS_MUTADOS 8

#define MAX_DADOS_GSM 30.0f
#define MAX_DADOS_WCDMA 80.0f
#define MAX_VOZ_GSM 125.0f
#define MAX_VOZ_WCDMA 150.0f

#define MAX_DADOS (MAX_DADOS_GSM + MAX_DADOS_WCDMA)
#define MAX_VOZ (MAX_VOZ_GSM + MAX_VOZ_WCDMA)

enum tipos_usuarios
{
    DADOS_GSM,
    DADOS_WCDMA,
    VOZ_GSM,
    VOZ_WCDMA
};

typedef struct cromossomo
{
    double dados_gsm = 0.0, dados_wcdma = 0.0;
    double voz_gsm = 0.0, voz_wcdma = 0.0;
    double fitness = 0.0;
    double media = 0.0;
} Cromossomo;

typedef struct {
    double dados_gsm = 0, dados_wcdma = 0;
    double voz_gsm = 0, voz_wcdma = 0;
} Quantizado;

typedef std::vector<Cromossomo> Populacao;

inline double gerar_usuarios(tipos_usuarios tipo)
{
    double value = 0.0;
    switch (tipo)
    {
    case DADOS_GSM:
        value = randfrom(0.0f, MAX_DADOS_GSM);
        break;
    case DADOS_WCDMA:
        value = randfrom(0.0f, MAX_DADOS_WCDMA);
        break;
    case VOZ_GSM:
        value = randfrom(0.0f, MAX_VOZ_GSM);
        break;
    case VOZ_WCDMA:
        value = randfrom(0.0f, MAX_VOZ_WCDMA);
    default:
        break;
    }
    return value;
}

inline double custo_gsm(double dados, double voz)
{
    return std::abs(30 - dados + ((6.0f / 25.0f) * voz));
}

inline double custo_wcdma(double dados, double voz)
{
    return std::abs(80 - dados + ((8.0f / 15.0f) * voz));
}

inline Quantizado quantizar(Cromossomo c)
{
    Quantizado q;
    q.voz_gsm = (c.dados_gsm / 125) * pow(2, 9) - 1;
    q.dados_gsm = (c.dados_gsm / 30) * pow(2, 9) - 1;
    q.voz_wcdma = (c.voz_wcdma / 150) * pow(2, 9) - 1;
    q.dados_wcdma = (c.dados_wcdma / 80) * pow(2, 9) - 1;

    return q; 
}

Cromossomo gerar_cromossomo();
Populacao gerar_populacao();
void printar_populacao(Populacao populacao);
void ordenar_populacao(Populacao &populacao);
Populacao selecionar(Populacao populacao);
Populacao cruzamento(Populacao populacao);
void mutacao(std::vector<std::string> &populacao);

#endif