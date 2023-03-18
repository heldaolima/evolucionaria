#include "expression.hpp"

#define is_eq(s1, s2) ((s1).compare((s2)) == 0)
#define pop(vec, var) {var = (vec).back(); (vec).pop_back();}

std::string operate(std::string val1, std::string op, std::string val2)
{
    lli n1 = std::stoll(val1), n2 = std::stoll(val2);

    if (is_eq(op, "+")) {
        return std::to_string(n1 + n2);
    }
    else if (is_eq(op, "-")) {
        return std::to_string(n1 - n2);
    }
    else if (is_eq(op, "*")) {
        return std::to_string(n1 * n2);
    }
    return "0";
}

lli calculate_expression(std::vector<Term> expr)
{
    int i = 0;
    std::vector<std::string> values;
    std::vector<std::string> operators;
    for (i = 0; i < expr.size(); i++) {
        if (expr[i].type == OPERADOR) {
            operators.push_back(expr[i].value);
        }
        else if (expr[i].type == NUMERO) {
            values.push_back(expr[i].value);
        }
        else if (expr[i].type == DELIMITADOR) {
            if (is_eq(expr[i].value, "(")) {
                operators.push_back(expr[i].value);
            }
            else if (is_eq(expr[i].value, "")) {
                while (!operators.empty() && !is_eq(operators.back(), "(")) {
                    std::string value1, value2, op;

                    pop(values, value1);
                    pop(values, value2);
                    pop(operators, op);

                    values.push_back(operate(value1, op, value2));
                }
                operators.pop_back();
            }
        }
    }

    std::string value1, value2, op;
    pop(values, value1);
    pop(values, value2);
    pop(operators, op);

    values.push_back(operate(value1, op, value2));
    return std::stoll(values.back());
}