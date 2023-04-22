#include "binario_utils.hpp"
#include <bitset>

std::string cromossomo_to_binario(Quantizado q)
{
    std::string binario = "";
    
    binario += std::bitset<8>(q.dados_gsm).to_string();
    binario += std::bitset<8>(q.voz_gsm).to_string();
    binario += std::bitset<8>(q.dados_wcdma).to_string();
    binario += std::bitset<8>(q.voz_wcdma).to_string();
    
    return binario;
}

std::vector<std::string> populacao_to_binario(Populacao p)
{
    std::vector<std::string> binarios(p.size());
    for (int i = 0; i < p.size(); i++) {
        binarios[i] = cromossomo_to_binario(quantizar(p[i]));
    }
    return binarios;
}

double desquantizar(std::string binario, tipos_usuarios tipo) 
{
    long long decimal = std::bitset<8>(binario).to_ullong();
    double result = 0.0;
    switch (tipo)
    {
    case VOZ_GSM:
        result += decimal * (125 / (pow(2, 9) - 1));
        break;
    case DADOS_GSM:
        result += decimal * (150 / (pow(2, 9) - 1));
        break;
    case VOZ_WCDMA:
        result += decimal * (150 / (pow(2, 9) - 1));
        break;
    case DADOS_WCDMA:
        result += decimal * (80 / (pow(2, 9) - 1));
        break;
    default:
        break;
    }
    
    return result;
}
