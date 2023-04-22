#ifndef _binario_utils_hpp
#define _binario_utils_hpp

#include <string>
#include <vector>
#include "genetico.hpp"

typedef struct {
    double dados_gsm = 0, dados_wcdma = 0;
    double voz_gsm = 0, voz_wcdma = 0;
} Quantizado;


inline Quantizado quantizar(Cromossomo c)
{
    Quantizado q;
    q.voz_gsm = (c.dados_gsm / 125) * pow(2, 9) - 1;
    q.dados_gsm = (c.dados_gsm / 30) * pow(2, 9) - 1;
    q.voz_wcdma = (c.voz_wcdma / 150) * pow(2, 9) - 1;
    q.dados_wcdma = (c.dados_wcdma / 80) * pow(2, 9) - 1;

    return q; 
}


std::string cromossomo_to_binario(Quantizado c);
std::vector<std::string> populacao_to_binario(Populacao p);
double desquantizar(std::string binario, tipos_usuarios tipo);


#endif