#ifndef _grammar_hpp_
#define _grammar_hpp_

#include <string>
#include <vector>

enum types {
    numero, operador, delimitador,
    production_t, production_s
};

#define QTD_PRODUCTIONS_S 2
#define QTD_PRODUCTIONS_T 2


typedef struct node{
    enum types type;
    std::string value;
    std::vector<node> next;
} Node;


/*
    S -> T + T | T - T
    T -> (S) | N
    N -> [0, 9]
*/

void production_S(Node &node, int index);
void production_T(Node &node, int index);
void production_N(Node &node);


#endif