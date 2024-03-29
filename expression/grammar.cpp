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
    int num = randint(QTD_NUMS);
    new_node(node, NUMERO, std::to_string(num), {});
}

Node get_node_at(Node &curr_node, int curr_position, int goal_position)
{
    if (curr_position == goal_position) {
        return curr_node;
    }

    for (Node next: curr_node.next){
        Node gotten = get_node_at(next, curr_position+1, goal_position);
        if (gotten.type != NOTHING) {
            return gotten;
        }
    }

    Node ans;
    new_node(ans, NOTHING, "", {});
    
    return ans;
}

bool swap_node_at(Node &curr_node, Node substitute, int curr_position, int goal_position)
{
    if (curr_position == goal_position) {
        curr_node = substitute;
        return true;
    }
    for (Node &next: curr_node.next) {
        if (swap_node_at(next, substitute, curr_position+1, goal_position)) {
            return true;
        }
    }
    return false;
}