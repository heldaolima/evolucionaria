#include <iostream>
#include <algorithm>
#include "grammar.hpp"
#include "expression.hpp"
#include "dbg.h"

#define NUMBER_OF_INDIVIDUALS 10
#define MUTATION_RATE 0.2

#define is_eq(s1, s2) ((s1).compare((s2)) == 0)

int GOAL = 0;

typedef struct individual {
    Node initial_node;
    std::vector<Term> expression;
    lli fitness_value = 0;
    int qtdNodes = 0;
} Individual;

typedef std::vector<Individual> Population;

void get_expression(Individual &ind, Node curr, int &size);
void evaluate_individual(Individual &ind);

void print_individual(Individual ind)
{
    std::cout << "Expression: ";
    for (Term t: ind.expression) {
        std::cout << t.value << " "; 
    }
    std::cout << "\n";
}

bool by_fitness_value(const Individual &a, const Individual &b)
{
    return a.fitness_value < b.fitness_value;
}

void sort_population(Population &population)
{
    std::sort(population.begin(), population.end(), by_fitness_value);
}

int count_mutable_nodes(Node curr, int count)
{
    if (curr.type == NUMERO || curr.type == OPERADOR) {
        count++;
    }

    for (Node next : curr.next) {
        count_mutable_nodes(next, count);
    }

    return count;
}

bool mutate_at(Node curr_node, int curr_position, int goal_position)
{
    if (curr_position == goal_position) {
        if (curr_node.type == NUMERO) {
            std::vector<int> numbers = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
            numbers.erase(numbers.begin() + std::stoi(curr_node.value));
            curr_node.value = std::to_string(numbers[randint(QTD_NUMS-1)]);
        }
        else if (curr_node.type == OPERADOR) {
            std::vector<std::string> operators = {"+", "-", "*"};
            for (int i = 0; i < QTD_PRODUCTIONS_S; i++) {
                if (is_eq(curr_node.value, operators[i])) {
                    operators.erase(operators.begin() + i);
                    break;
                }
            }
            curr_node.value = operators[randint(QTD_PRODUCTIONS_S)];
        }
        return true;
    }

    if (curr_node.type == NUMERO || curr_node.type == OPERADOR) {
        curr_position++;
    }

    for (Node next: curr_node.next) {
        if (mutate_at(next, curr_position, goal_position)) {
            return true;
        }
    }
    return false;
}

void mutation(Population &population)
{
    double prob = 0;
    int count_mutables = 0, random_position = 0;
    for (Individual &ind : population) {
        prob = random_double();
        if (prob < MUTATION_RATE) {
            Individual mutated = ind;
            
            count_mutables = count_mutable_nodes(mutated.initial_node, 0);
            random_position = randint(count_mutables);        
        }
    }
}

Individual reproduce(Individual parent1, Individual parent2)
{
    Individual offspring;

    int less_nodes = (parent1.qtdNodes < parent2.qtdNodes) ? parent1.qtdNodes : parent2.qtdNodes;

    int random_position = randint(less_nodes);
    
    Node from_p1 = get_node_at(parent1.initial_node, 0, random_position);
    Node from_p2 = get_node_at(parent2.initial_node, 0, random_position);
    
    int qtd_nodes = 0;
    if (
        (from_p1.type == OPERADOR && from_p2.type == OPERADOR) ||
        (from_p1.type == NUMERO && from_p2.type == NUMERO)
    ) {
        offspring.initial_node = parent1.initial_node;
        swap_node_at(offspring.initial_node, from_p2, 0, random_position);
        
        get_expression(offspring, offspring.initial_node, qtd_nodes);

        offspring.qtdNodes = qtd_nodes;
        evaluate_individual(offspring);
    }

    return offspring;
}

void reproduction(Population &population)
{
    int i = 0, j = 0;
    for (i = 0; i < population.size(); i++) {
        for (j = i+1; j < population.size(); j++) {
            Individual offspring1 = reproduce(population[i], population[j]);
            Individual offspring2 = reproduce(population[j], population[i]);

            if (offspring1.qtdNodes != 0 && 
                offspring1.fitness_value < population[i].fitness_value) 
            {
                population[i] = offspring1;
            }
            if (offspring2.qtdNodes != 0 && 
                offspring2.fitness_value < population[j].fitness_value)
            {
                population[j] = offspring2;
            }
        }
    }
}

inline double average_adaptation(Population population)
{
    double mean = 0.0;
    for (Individual ind : population) {
        mean += ind.fitness_value;
    }
    return (mean / population.size());
}

void evaluate_individual(Individual &ind)
{
    lli fitness = calculate_expression(ind.expression);
    ind.fitness_value = std::abs(fitness - GOAL);
}

lli best_fitness(Population &population)
{
    int i = 0;
    int fitness;
    for (i = 0; i < population.size(); i++) {
        if (i == 0) 
            fitness = population[i].fitness_value;
        else if (population[i].fitness_value < fitness)
            fitness = population[i].fitness_value;
    }

    return fitness;
}

void get_expression(Individual &ind, Node curr, int &size)
{
    ++size;
    if (curr.next.size() == 0) {
        Term t;
        t.value = curr.value;
        t.type = curr.type;
        ind.expression.push_back(t);
        return;
    }

    for (Node next: curr.next) {
        get_expression(ind, next, size);
    }
}

Individual generate_individual()
{
    int qtdNodes = 0;
    Individual ind;
    production_S(ind.initial_node, 0);

    get_expression(ind, ind.initial_node, qtdNodes);
    ind.qtdNodes = qtdNodes;

    return ind;
}

Population generate_population()
{
    Population population(NUMBER_OF_INDIVIDUALS);
    int i = 0;
    for (i = 0; i < NUMBER_OF_INDIVIDUALS; i++) 
    {
        population[i] = generate_individual();
        evaluate_individual(population[i]);
    }

    return population;
}

Population genetic(Population population)
{
    Population new_population;

    return new_population;
}

int main(int argc, char* argv[])
{
    seed();
    Population population;
    lli best_fit;
    double adaptation = 0.0;
    check(argc >= 2, "USO: ./main <numero>");
    
    GOAL = atoi(argv[1]);

    population = generate_population();
    best_fit = best_fitness(population);
    
    while (best_fit != 0) {
        sort_population(population);
        adaptation = average_adaptation(population);

        reproduction(population);
        mutation(population);
        
        best_fit = best_fitness(population);
    }
    sort_population(population);
    print_individual(population[0]);

    return 0;

error:
    return 1;
}