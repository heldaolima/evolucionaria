#ifndef _expression_hpp_
#define _expresion_hpp_

#include "grammar.hpp"

typedef struct term {
    std::string value;
    enum types type;
} Term;

std::string operate(std::string val1, std::string op, std::string val2);
lli calculate_expression(std::vector<Term> expr);

#endif