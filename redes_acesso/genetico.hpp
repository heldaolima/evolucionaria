#ifndef _genetico_hpp
#define _genetico_hpp

#include "dbg.h"
#include <iostream>
#include <cstdlib>
#include <vector>

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
} Cromossomo;

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

double fitness(Cromossomo individuo);
void printar_populacao(Populacao populacao);
Cromossomo gerar_cromossomo();
Populacao gerar_populacao();

#endif