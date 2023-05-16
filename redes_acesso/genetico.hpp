#ifndef _genetico_hpp
#define _genetico_hpp

#include "dbg.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <fstream>

#define seed() (srand((unsigned)time(NULL)))
#define randint(n) (rand() % n)
#define randint_interval(i, n) (i + randint(n))
#define print_vec(V) \
    for (auto n : V) \
        std::cout << n << " ";
#define random_double() (rand() / static_cast<double>(RAND_MAX))

inline double doubleRandfrom(double min, double max) 
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

#define DADOS_GSM_ORIGINAL 30.0f
#define DADOS_WCDMA_ORIGINAL 80.0f
#define VOZ_GSM_ORIGINAL 125.0f
#define VOZ_WCDMA_ORIGINAL 150.0f

static double MAX_DADOS_GSM = 0;
static double MAX_DADOS_WCDMA = 0;
static double MAX_VOZ_GSM = 0;
static double MAX_VOZ_WCDMA = 0;

#define MAX_LIM 500.0f

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


typedef std::vector<Cromossomo> Populacao;

#define caminho "entrada.txt"

static void print_limites()
{
    std::cout << MAX_DADOS_GSM << "\n";
    std::cout << MAX_DADOS_WCDMA << "\n";
    std::cout << MAX_VOZ_GSM << "\n";
    std::cout << MAX_VOZ_WCDMA << "\n";
    std::cout << "\n";
}

static void ler_valores_do_arquivo() 
{
    std::ifstream input(caminho);
    if (!input.is_open()) {
        std::cout << "Erro ao abrir arquivo\n";
        exit(0);
    }

    std::string linha = "";
    int i = 0;
    while (std::getline(input, linha)) {
        switch (i)
        {
        case 0:
            MAX_DADOS_GSM = stof(linha);
            break;
        case 1:
            MAX_DADOS_WCDMA = stof(linha);
            break;
        case 2:
            MAX_VOZ_GSM = stof(linha);
            break;
        case 3:
            MAX_VOZ_WCDMA = stof(linha);
            break;
        default:
            break;
        }
        i++;
    }
    input.close();
}

static void gerar_novos_limites()
{
    std::ofstream outputFile(caminho, std::ios::trunc);
    if (outputFile.is_open()) {
        outputFile << doubleRandfrom(0.0f, MAX_LIM) << "\n"; 
        outputFile << doubleRandfrom(0.0f, MAX_LIM) << "\n";    
        outputFile << doubleRandfrom(0.0f, MAX_LIM) << "\n";    
        outputFile << doubleRandfrom(0.0f, MAX_LIM) << "";

        outputFile.close();

        ler_valores_do_arquivo();
    } else {
        std::cout << "Erro ao abrir o arquivo\n";
        exit(0);
    }
}

static void restaurar_limites()
{
    std::ofstream outputFile(caminho, std::ios::trunc);
    if (outputFile.is_open()) {
        outputFile << DADOS_GSM_ORIGINAL << ".0\n"; 
        outputFile << DADOS_WCDMA_ORIGINAL << ".0\n";
        outputFile << VOZ_GSM_ORIGINAL << ".0\n";
        outputFile << VOZ_WCDMA_ORIGINAL << ".0";

        outputFile.close();
    }
}

inline double gerar_usuarios(tipos_usuarios tipo)
{
    double value = 0.0;
    switch (tipo)
    {
    case DADOS_GSM:
        value = doubleRandfrom(0.0f, MAX_DADOS_GSM);
        break;
    case DADOS_WCDMA:
        value = doubleRandfrom(0.0f, MAX_DADOS_WCDMA);
        break;
    case VOZ_GSM:
        value = doubleRandfrom(0.0f, MAX_VOZ_GSM);
        break;
    case VOZ_WCDMA:
        value = doubleRandfrom(0.0f, MAX_VOZ_WCDMA);
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

Cromossomo gerar_cromossomo();
Populacao gerar_populacao();
bool acima_dos_limites(Cromossomo c);
void printar_populacao(Populacao populacao);
void ordenar_populacao(Populacao &populacao);
Populacao selecionar(Populacao populacao);
void cruzamento(std::vector<std::string> &populacao);
void mutacao(std::string &cromossomo);
Populacao decodificar_populacao(std::vector<std::string> binarios);

#endif