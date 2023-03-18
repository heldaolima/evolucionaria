#include <iostream>
#include "grammar.hpp"
#include "expression.hpp"
#include "dbg.h"

#define NUMBER_OF_INDIVIDUALS 10
int GOAL = 0;

typedef struct individual {
    Node initial_node;
    std::vector<Term> expression;
    lli fitness_value = 0;
    int qtdNodes = 0;
} Individual;

typedef std::vector<Individual> Population;

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
        population[i].fitness_value = evaluate_individual(population[i]);
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
    check(argc >= 2, "USO: ./main <numero>");
    
    GOAL = atoi(argv[1]);

    Population population = generate_population();
    lli best_fit = best_fitness(population);
    // found it => 0



    return 0;

error:
    return 1;
}