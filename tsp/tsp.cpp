#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdlib>
#include <math.h>
#include <random>
#include "dbg.h"

#define RANDOM_PARENTS

#define NUM_CITIES 25
#define POP_SIZE 100
#define ELITE_SIZE 20
#define MUTATION_RATE 0.01
#define MAX_ITERATIONS 1000

#define seed() (srand((unsigned) time(NULL)))
#define randint(n) (rand() % n)
#define randint_interval(i, n) (i + randint(n))
#define func_each_vec(V, F) for(auto n: V) F(n)
#define random_double() (rand() / static_cast<double>(RAND_MAX))

#define deltaX(A, B) ((double) std::abs((A).x - (B).x))
#define deltaY(A, B) ((double) std::abs((A).y - (B).y))
#define distance_cities(A, B) (sqrt(pow(deltaX(A, B), 2) + pow(deltaY(A, B), 2)))

typedef struct city {
    int x;
    int y;
} City;

#define print_coord(C) (std::cout << "(" << (C).x << ", " << (C).y << "); ")

typedef struct individual {
    std::vector<City> route;
    double fitness_value = 0.0;
} Individual;

typedef std::vector<Individual> Population;

bool fit_check(Individual a, Individual b)
{
    return a.fitness_value < b.fitness_value;
}

double fitness(std::vector<City> route)
{
    double distance = 0.0; 
    int i = 0;
    City from, to;
    
    for (i = 0; i < NUM_CITIES; i++) {
        from = route[i];
        to = route[(i+1) % NUM_CITIES];
        distance += distance_cities(from, to);
        // debug("distance from (%d, %d) to (%d, %d)=(%lf)", from.x, from.y, to.x, to.y, distance_cities(from, to));
    }

    return 1 / distance;
}

std::vector<City> generate_chromossome(std::vector<City> cities)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cities.begin(), cities.end(), g); // does not work when repeated
    return cities;
}

Population generate_population(std::vector<City> cities) 
{
    Population population(POP_SIZE);

    for (int i = 0; i < POP_SIZE; i++) {
        // generate_chromossome(cities);
        population[i].route = generate_chromossome(cities);
        population[i].fitness_value = fitness(population[i].route);
    }

    return population;
}

void swap_cities(City *a, City *b)
{
    City aux = *a;
    *a = *b;
    *b = aux;
}

void mutate(Individual *child) 
{
    int index_swap = 0;
    double random_d = 0.0;
    for (int i = 0; i < NUM_CITIES; i++) {
        random_d = random_double();
        // debug("random double: %lf", random_d);
        if (random_d < MUTATION_RATE) {
            index_swap = randint(NUM_CITIES);
            // debug("index swap: %d", index_swap);
            swap_cities(&child->route[i], &child->route[index_swap]);
        }
    }
    child->fitness_value = fitness(child->route);
}

Individual crossover(Individual parent1, Individual parent2)
{
    Individual child;
    int pivot = randint(parent1.route.size());
    int i = 0;
    
    for (i = 0; i < NUM_CITIES; i++) {
        (i < pivot) 
            ? child.route.push_back(parent1.route[i])
            : child.route.push_back(parent2.route[i]);
    }
    child.fitness_value = fitness(child.route);
    
    return child;
}

Population selection(Population population) 
{
    sort(population.begin(), population.end(), fit_check);
    return {population[0], population[1]}; //fittest
}

Population GA(Population population)
{
    Population parents, new_population(POP_SIZE);
    Individual child;
    
    for (int i = 0; i < POP_SIZE; i++) {
        #ifdef RANDOM_PARENTS
            int idx1 = 0, idx2 = 0;
            do {
                idx1 = randint(POP_SIZE);
                idx2 = randint(POP_SIZE);
            } while (idx1 == idx2);
            child = crossover(population[idx1], population[idx2]);
        #else
            parents = selection(population);
            child = crossover(parents[0], parents[1]);
        #endif
        mutate(&child);
        new_population[i] = child;
        parents.clear();
    }

    return new_population;
}

void test_shuffle(std::vector<City> cities)
{
    generate_chromossome(cities);
}

int main(int argc, char* argv[])
{
    seed();
    unsigned int i = 0;
    
    std::vector<City> cities(NUM_CITIES);

    for (i = 0; i < NUM_CITIES; i++) {
        cities[i] = {randint(200), randint(200)};
    }

    Population population = generate_population(cities);

    for (auto each: population) {
        std::cout << "\n";
        func_each_vec(each.route, print_coord);
        std::cout << " fitness = " << each.fitness_value << "\n";
    }
    i = 0;

    while (i < MAX_ITERATIONS) {
        population = GA(population);
        i++;
    }

    std::cout << "Iteration number " << i << "\n";
    for (auto each: population) {
        func_each_vec(each.route, print_coord);
        std::cout << " Fitness value: " << each.fitness_value << "\n\n";
    }

    std::cout << "Best result: \n";
    sort(population.begin(), population.end(), fit_check);
    func_each_vec(population[0].route, print_coord);
    std::cout << " Fitness value: " << population[0].fitness_value << "\n";

    return 0;
}