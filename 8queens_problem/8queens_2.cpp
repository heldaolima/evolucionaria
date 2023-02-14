#define NDEBUG
#define UNLIMITED

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include "dbg.h"

#define seed() (srand((unsigned) time(NULL)))
#define randint(n) (rand() % n)
#define randint_interval(i, n) (i + randint(n))
#define print_vec(V) for(auto n: V) std::cout << n << " ";
#define random_double() (rand() / static_cast<double>(RAND_MAX))

#define NQUEENS 8
#define POPULATION_SIZE 10
#define MAX_FITNESS 28
#define MAX_ITERATION 1000

typedef struct individual {
    std::vector<int> sequence;
    int fitness_value;
    double survival_value;
} Individual;

typedef std::vector<Individual> Population;

inline void print_individual(Individual ind) 
{
    std::cout << "[ ";
    print_vec(ind.sequence);
    std::cout << "] fitness = " << ind.fitness_value << "\n";
}

#define print_pop(P) for (auto ind: P) print_individual(ind);

std::vector<int> unique_elements(std::vector<int> vec)
{
    std::sort(vec.begin(), vec.end());

    std::vector<int>::iterator it;
    it = std::unique(vec.begin(), vec.end());
    vec.resize(std::distance(vec.begin(), it));
    return vec;
}

int fitness(std::vector<int> sequence)
{
    int i = 0, j = 0, dx, dy;
    std::vector<int> unique_values = unique_elements(sequence);

    // pode comecar com 0 -> verifica ataques nas linhas e nas colunas
    int ataques = std::abs( (int) (sequence.size() - unique_values.size()));
    
    // diagonais
    for (i = 0; i < sequence.size(); i++) {
        for (j = 0; j < sequence.size(); j++) {
            if (i != j) {
                dx = std::abs(i - j);
                dy = std::abs(sequence[i] - sequence[j]);
                ataques += (dx == dy) ? 1 : 0;
            }
        }
    }

    return MAX_FITNESS - ataques;
}

void swap_child(Individual *c1, Individual *c2) {
    Individual temp;
    temp = *c1;
    *c1 = *c2;
    *c2 = temp;
}

Individual crossover(Population parents)
{
    int i = 0;
    debug("pai1 size: %lu", parents[0].sequence.size());
    int pivot = randint(parents[0].sequence.size());
    debug("pivot: %d", pivot);
    Individual child1, child2, temp;

    for (i = 0; i < parents[0].sequence.size(); i++) {
        (i < pivot) ? child1.sequence.push_back(parents[0].sequence[i]) : 
        child1.sequence.push_back(parents[1].sequence[1]);
    }

    child1.fitness_value = fitness(child1.sequence);
    
    if (child1.fitness_value > parents[0].fitness_value) {
        swap_child(&child1, &parents[0]);
    }
    
    for (i = 0; i < parents[0].sequence.size(); i++) {
        (i < pivot) ? child2.sequence.push_back(parents[1].sequence[i]) :
        child2.sequence.push_back(parents[0].sequence[i]);
    }

    child2.fitness_value = fitness(child2.sequence);

    if (child2.fitness_value > parents[1].fitness_value) {
        swap_child(&child2, &parents[1]);
    }

    return child1;
}

void mutate(Individual* child) 
{
    int num = randint(NQUEENS);
    debug("num: %d", num);

    child->sequence[num] = randint(NQUEENS);
    child->fitness_value = fitness(child->sequence);
}

Population selection(Population population)
{
    int somatorio_fitness = 0;
    double p1_rand = 0.0, p2_rand = 0.0;
    Population p1_rn, p2_rn;

    Individual parent1, parent2; 
    
    for (auto indiv: population) {
        somatorio_fitness += indiv.fitness_value;
    }

    debug("somatorio: %d", somatorio_fitness);

    for (int i = 0; i < population.size(); i++) {
        population[i].survival_value = (double) population[i].fitness_value / (somatorio_fitness * 1.0);
    }

    while (true) {
        p1_rn.clear();
        debug("cleared p1");

        p1_rand = random_double();
        debug("got p1_random: %lf", p1_rand);

        for (auto indiv: population) {
            if (indiv.survival_value <= p1_rand) {
                p1_rn.push_back(indiv);
            }
        }
        
        debug("filled p1_rn");
        
        if (p1_rn.size() == 0){ 
            debug("p1_rn has size zero");
            continue;
        }
        parent1 = p1_rn[0];
        break;
    }

    while (true) {
        p2_rn.clear();
        debug("cleared p2");

        p2_rand = random_double();
        debug("got p2 rand: %lf", p2_rand);

        for (auto indiv: population) {
            if (indiv.survival_value <= p2_rand) {
                p2_rn.push_back(indiv);
            }
        }
        debug("filled p2_rn");

        if (p2_rn.size() == 0){ 
            debug("p2_rn has size zero.");
            continue;
        }
        
        debug("this is the size of p2_rn: %lu", p2_rn.size());
        int t = randint(p2_rn.size());
        debug("got randint t: %d", t);

        parent2 = p2_rn[t];
        debug("assigned");
        if (parent1.sequence != parent2.sequence) {
            debug("checked sequences");
            break;
        }
        else {
            continue;
        }
    }
    
    Population parents = {parent1, parent2};
    return parents; 
}

std::vector<int> generate_chromossome()
{
    std::vector<int> sequence(NQUEENS);

    for (int i = 0; i < NQUEENS; i++) {
        sequence[i] = randint(NQUEENS);
    }

    return sequence;
}

Population generate_population()
{
    Population population(POPULATION_SIZE);

    for (int i = 0; i < POPULATION_SIZE; i++) {
        population[i].sequence = generate_chromossome();
        population[i].fitness_value = fitness(population[i].sequence);
    }

    return population;
}

Population genetico(Population population)
{
    Population parents, new_pop;
    Individual child;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        
        parents = selection(population);
        debug("got parents");
        child = crossover(parents);
        debug("crossover parents");
        mutate(&child);
        debug("mutated child");

        new_pop.push_back(child);

        parents.clear();
    }
    return new_pop;
}

#ifdef UNLIMITED
bool stop_condition(Population population)
{
    std::vector<int> fitness_values;
    for (auto each: population) {
        fitness_values.push_back(each.fitness_value);
    }

    for (auto each: population) {
        if (each.fitness_value == MAX_FITNESS) {
            return true;
        }
    }

    return false;
}

#else
bool stop_condition(Population population, unsigned int i)
{
    std::vector<int> fitness_values;
    for (auto each: population) {
        fitness_values.push_back(each.fitness_value);
    }

    for (auto each: population) {
        if (each.fitness_value == MAX_FITNESS) {
            return true;
        }
    }

    if (i == MAX_ITERATION) {
        return true;
    }

    return false;
}

#endif

int main(int argc, char* argv[])
{
    unsigned int i = 0;
    seed();

    Population population = generate_population();

    #ifdef UNLIMITED
    while (!stop_condition(population)) {
        population = genetico(population);
        i++;
    }
    #else
    while (!stop_condition(population, i)) {
        population = genetico(population);
        i++;
    }
    #endif

    std::cout << "Iteration number " << i << "\n";    
    print_pop(population);

    for (auto each: population) {
        if (each.fitness_value == MAX_FITNESS) {
            std::cout << "\nFound optimal: \n";
            print_individual(each);
        }
    }
    
    return 0;
}