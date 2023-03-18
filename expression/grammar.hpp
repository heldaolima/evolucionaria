#ifndef _grammar_hpp_
#define _grammar_hpp_

#include <string>
#include <vector>
#include <cstdlib>

#define seed() (srand((unsigned)time(NULL)))
#define randint(n) (rand() % n)
#define randint_interval(i, n) (i + randint(n))

#define QTD_PRODUCTIONS_S 2
#define QTD_PRODUCTIONS_T 2

enum types {
    NUMERO, OPERADOR, DELIMITADOR,
    PRODUCTION_S, PRODUCTION_T
};

typedef long long int lli;

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