#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

ifstream arquivo;

vector<float> LerArquivo(string caminho)
{
  vector<float> variaveis;

  ifstream input(caminho);
  if (!input.is_open()) {
    cout << "Erro ao abrir arquivo" << endl;
    return {};
  }
  string linha;
  int i = 0;
  while (getline(input, linha)) {
    //cout << linha << endl;
    variaveis.push_back(stof(linha));
  }
  input.close();

  return variaveis;
}

// int main() {
//   const string arquivo = "entrada.txt";
//   for (int i = 0; i < 10000; i++) {
//     vector<float> variaveis = LerArquivo(arquivo);
//     for (int j = 0; j < variaveis.size(); j++)
//     {
//       if (j == 0) cout << "MAX_DADOS_GSM: ";
//       if (j == 1) cout << "MAX_DADOS_WCDMA: ";
//       if (j == 2) cout << "MAX_VOZ_GSM: ";
//       if (j == 3) cout << "MAX_VOZ_WCDMA: ";
//       cout << variaveis[j] << endl;
//     }
//   }
//   return 0;
// }