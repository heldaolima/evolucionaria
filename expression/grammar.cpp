#include "grammar.hpp"

inline void new_node(Node &node, types type, std::string value, std::vector<Node> next)
{
    node.type = type;
    node.value = value;
    node.next = next;
}

void production_S(Node &node, int index)
{
    int i = randint(QTD_PRODUCTIONS_S);
    std::string value;
    Node next1, next2, next3;
    production_T(next1, index+1);
    
    if (i == 0) {    
        new_node(next2, OPERADOR, "+", {});
        value = "T+T";
    }
    else if (i == 1) {
        new_node(next2, OPERADOR, "-", {});
        value = "T-T";
    }

    production_T(next3, index+2);
    new_node(node, PRODUCTION_S, value, {next1, next2, next3});
}

void production_T(Node &node, int index)
{
    Node next1;
    if (index > 10) {
        production_N(next1);
        new_node(node, PRODUCTION_T, "N", {next1});
    }
    else {
        int i = randint(QTD_PRODUCTIONS_T);

        if (i == 0) {
            Node next2, next3;
            new_node(next1, DELIMITADOR, "(", {});
            
            production_S(next2, index+1);

            new_node(next3, DELIMITADOR, ")", {});
            new_node(node, PRODUCTION_T, "(S)", {next1, next2, next3});
        }
        else if (i == 1) {
            production_N(next1);
            new_node(node, PRODUCTION_T, "D", {next1});
        }
    }
}

void production_N(Node &node)
{
    int num = randint(10);
    new_node(node, NUMERO, std::to_string(num), {});
}