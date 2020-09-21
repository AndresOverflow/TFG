#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Individual.h"
#include "Population.h"
#include "MutationProbabilityTable.h"
#include "armadillo.h"
#include "TableFandCR.h"

//TODO raro que el bestIndividual siempre sea el mismo al principio
//problema el mutation size ha de ser divisor del population_size_init



void cec14_test_func(double *, double *, int, int, int);

double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;

using namespace std;
using namespace arma;

//static const double F = 1.7; //mutate factor
static const double F = 0.7; //mutate factor
static const double CR = 0.15; //Crossover factor
//static const double CR = 0.15; //Crossover factor
static const int GROUP_SIZE_INIT = Population::POPULATION_SIZE_INIT/MutationProbabilityTable::MUTATION_STRATEGIES;
static const double EVAPORATION_RATE = 0.2;
static const int LP_RAM = 100;
static const int UPPER_BOUND = 100;
static const int LOWER_BOUND = -100;
const double EPSILON = pow(10.0, -8);
const int MAX_FITNESS_EVALUATIONS = Individual::DIMENSION * 10000;

typedef Individual (*MutationFunctions)(vector<Individual> current_population, int ind, double p);

//TODO: Question, mutation table with probabilities that sum more that 1?
//TODO: Question, cuantas fitness operations? porque para hacer la mutacion también los calculo


//Return random value with uniform distribution [0, 1)
double rand_double() {
    return (double) rand() / (double) RAND_MAX;
}

//TODO: cheeck If random functions are working
/*
  Return random value from Cauchy distribution with mean "mu" and variance "gamma"
*/
double rand_cauchy(double mu, double gamma) {
    double result = 0.0;
    result = mu + gamma * tan(M_PI * (rand_double() - 0.5));
    if (result < 0)  result = 0.0;
    if (result > 1)  result = 1.0;

    return result;
}


/*
  Return random value from normal distribution with mean "mu" and variance "gamma"
*/
double rand_gauss(double mu, double sigma) {
    double result = 0;
    result = mu + sigma * sqrt(-2.0 * log(rand_double())) * sin(2.0 * M_PI * rand_double());
    while (result < 0) {
        result = mu + sigma * sqrt(-2.0 * log(rand_double())) * sin(2.0 * M_PI * rand_double());
    }
    if (result > 1)  result = 1.0;

    return result;

}


Population selection(Population current_population, Population offspring, int number_of_function) {
    Population final_population = Population(current_population.getPopulationSize());
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector = offspring.getIndividuals();


    //cout << "selection function";
    //TODO cambiar el numero de individuos en funcion del population size
    vector<Individual> final_population_vector = final_population.getIndividuals();

    for (int i = 0; i < current_population.getPopulationSize(); i++) {
        if (current_population_vector[i].betterFitnessThan(offspring_vector[i], number_of_function)) {
            final_population_vector[i].setComponents(current_population_vector[i].getComponents());
            final_population_vector[i].setFitness(current_population_vector[i].getFitness());
        } else {
            final_population_vector[i].setComponents(offspring_vector[i].getComponents());
            final_population_vector[i].setFitness(offspring_vector[i].getFitness());
        }
        final_population_vector[i].setGroup(current_population_vector[i].getGroup());
    }

    final_population.setIndividuals(final_population_vector);
    return final_population;
}

//TODO problem with population_size of offspring
//binomial crossover
Population crossover(Population current_population, Population mutated_population) {
    Population offspring = Population(current_population.getPopulationSize());

    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> mutated_population_vector = mutated_population.getIndividuals();
    vector<Individual> offspring_vector = offspring.getIndividuals();

    float random_value;
    int j_random;
    double value;

    //por cada individuo de la poblacion
    for (int individual_i = 0; individual_i < current_population.getPopulationSize(); individual_i++) {
        //generamos escogemos una componente
        j_random = (random() % current_population.getPopulationSize());
        //por cada componente
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {
            // generar un numero random de 0 a 1
            random_value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            // si el numero es menor que CR o es el indice j entonces es la componente mutada
            // si es mayor que CR y no es j entonces es la componente original
            if (random_value <= CR or component_i == j_random) {
                value = mutated_population_vector[individual_i].getComponent(component_i);
                offspring_vector[individual_i].setComponent(component_i, value);

                //offspring_vector[individual_i].setGroup(current_population_vector[individual_i].getGroup());
            } else {
                value = current_population_vector[individual_i].getComponent(component_i);
                offspring_vector[individual_i].setComponent(component_i, value);

                //offspring_vector[individual_i].setGroup(current_population_vector[individual_i].getGroup());
            }
        }
    }


    offspring.setIndividuals(offspring_vector);
    offspring.recalculateFitness();

    return offspring;

}


/*
 * realiza la mutación de una población y devuelve el el vector mutado
 */




vector<Individual> DE_rand_1(vector<Individual> current_population_vector) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3;
    double CN_X_r1, CN_X_r2, CN_X_r3;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < current_population_vector.size(); i++) {
        N_X_r1 = (rand() % current_population_vector.size());
        N_X_r2 = (rand() % current_population_vector.size());
        N_X_r3 = (rand() % current_population_vector.size());

        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];

            value = CN_X_r1 + F * (CN_X_r2 - CN_X_r3);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;

}

vector<Individual> DE_rand_2(vector<Individual> current_population_vector) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3, N_X_r4, N_X_r5;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_r4, CN_X_r5;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < current_population_vector.size(); i++) {
        N_X_r1 = (rand() % current_population_vector.size());
        N_X_r2 = (rand() % current_population_vector.size());
        N_X_r3 = (rand() % current_population_vector.size());
        N_X_r4 = (rand() % current_population_vector.size());
        N_X_r5 = (rand() % current_population_vector.size());

        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];
            CN_X_r4 = current_population_vector[N_X_r4].getComponents()[component_i];
            CN_X_r5 = current_population_vector[N_X_r5].getComponents()[component_i];


            value = CN_X_r1 + F * (CN_X_r2 - CN_X_r3 + CN_X_r4 - CN_X_r5);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;
}

vector<Individual> DE_best_1(vector<Individual> current_population_vector) {
    vector<Individual> mutated_vector;
    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_best;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < current_population_vector.size(); i++) {
        N_X_r1 = (rand() % current_population_vector.size());
        N_X_r2 = (rand() % current_population_vector.size());


        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_best = best_individual_components[component_i];


            value = CN_X_best + F * (CN_X_r1 - CN_X_r2);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;
}

vector<Individual> DE_best_2(vector<Individual> current_population_vector) {
    vector<Individual> mutated_vector;
    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3, N_X_r4;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_r4, CN_X_best;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < current_population_vector.size(); i++) {
        N_X_r1 = (rand() % current_population_vector.size());
        N_X_r2 = (rand() % current_population_vector.size());
        N_X_r3 = (rand() % current_population_vector.size());
        N_X_r4 = (rand() % current_population_vector.size());


        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];
            CN_X_r4 = current_population_vector[N_X_r4].getComponents()[component_i];
            CN_X_best = best_individual_components[component_i];


            value = CN_X_best + F * (CN_X_r1 - CN_X_r2 + CN_X_r3 - CN_X_r4);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;
}

vector<Individual> DE_currentToRandom_1(vector<Individual> current_population_vector) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_i;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < current_population_vector.size(); i++) {
        N_X_r1 = (rand() % current_population_vector.size());
        N_X_r2 = (rand() % current_population_vector.size());
        N_X_r3 = (rand() % current_population_vector.size());



        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_i = current_population_vector[i].getComponents()[component_i];

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];


            value = CN_X_i + F * (CN_X_r1 - CN_X_i + CN_X_r2 - CN_X_r3);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;
}

vector<Individual> DE_currentToBest_1(vector<Individual> current_population_vector) {

    vector<Individual> mutated_vector;
    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_i, CN_X_best;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < current_population_vector.size(); i++) {
        N_X_r1 = (rand() % current_population_vector.size());
        N_X_r2 = (rand() % current_population_vector.size());



        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_i = current_population_vector[i].getComponents()[component_i];

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_best = best_individual_components[component_i];


            value = CN_X_i + F * (CN_X_best - CN_X_i + CN_X_r1 - CN_X_r2);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;
}

Individual DE_rand_1_ind(vector<Individual> current_population_vector, int ind) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2, N_X_r3;
    double CN_X_r1, CN_X_r2, CN_X_r3;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());
    N_X_r3 = (rand() % current_population_vector.size());

    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];

        value = CN_X_r1 + F * (CN_X_r2 - CN_X_r3);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;

}

Individual DE_rand_2_ind(vector<Individual> current_population_vector, int ind) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }
    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2, N_X_r3, N_X_r4, N_X_r5;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_r4, CN_X_r5;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());
    N_X_r3 = (rand() % current_population_vector.size());
    N_X_r4 = (rand() % current_population_vector.size());
    N_X_r5 = (rand() % current_population_vector.size());

    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];
        CN_X_r4 = current_population_vector[N_X_r4].getComponents()[component_i];
        CN_X_r5 = current_population_vector[N_X_r5].getComponents()[component_i];


        value = CN_X_r1 + F * (CN_X_r2 - CN_X_r3 + CN_X_r4 - CN_X_r5);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}

Individual DE_best_1_ind(vector<Individual> current_population_vector, int ind) {
    vector<Individual> mutated_vector;
    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_best;

    double value;

//Por cada individuo de la población
//escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());


    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_best = best_individual_components[component_i];


        value = CN_X_best + F * (CN_X_r1 - CN_X_r2);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}

Individual DE_best_2_ind(vector<Individual> current_population_vector, int ind) {
    vector<Individual> mutated_vector;
    Population current_population = Population(current_population_vector.size());
    int number = current_population_vector.size();
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2, N_X_r3, N_X_r4;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_r4, CN_X_best;

    double value;

//Por cada individuo de la población
//escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());
    N_X_r3 = (rand() % current_population_vector.size());
    N_X_r4 = (rand() % current_population_vector.size());


    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];
        CN_X_r4 = current_population_vector[N_X_r4].getComponents()[component_i];
        CN_X_best = best_individual_components[component_i];


        value = CN_X_best + F * (CN_X_r1 - CN_X_r2 + CN_X_r3 - CN_X_r4);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}

Individual DE_currentToRandom_1_ind(vector<Individual> current_population_vector, int ind) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }
    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2, N_X_r3;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_i;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());
    N_X_r3 = (rand() % current_population_vector.size());



    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_i = current_population_vector[ind].getComponents()[component_i];

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];


        value = CN_X_i + F * (CN_X_r1 - CN_X_i + CN_X_r2 - CN_X_r3);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}

//TODO to be checked
Individual DE_currentToBest_1_ind(vector<Individual> current_population_vector, int ind) {
    vector<Individual> mutated_vector;
    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_best, CN_X_i;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());


    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_i = current_population_vector[ind].getComponents()[component_i];

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_best = best_individual_components[component_i];


        value = CN_X_i + F * (CN_X_best - CN_X_i + CN_X_r1 - CN_X_r2);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}


Individual DE_PBest_1_ind(vector<Individual> current_population_vector, int ind, double p) {
    vector<Individual> mutated_vector;

    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);

    vector<double> pbest_individual_components = current_population.pBestIndividual(p).getComponents();

    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_pbest;

    double value;

//Por cada individuo de la población
//escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());


    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_pbest = pbest_individual_components[component_i];


        value = CN_X_pbest + F * (CN_X_r1 - CN_X_r2);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}

Individual DE_currentToPBest_1_ind(vector<Individual> current_population_vector, int ind, double p) {
    vector<Individual> mutated_vector;

    Population current_population = Population(current_population_vector.size());
    current_population.setIndividuals(current_population_vector);
    vector<double> pbest_individual_components = current_population.pBestIndividual(p).getComponents();

    for (int i = 0; i < current_population_vector.size(); i++) {
        mutated_vector.insert(mutated_vector.begin(), Individual());
    }

    Individual ind_to_return = Individual();

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_pbest, CN_X_i;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    N_X_r1 = (rand() % current_population_vector.size());
    N_X_r2 = (rand() % current_population_vector.size());


    //Por cada componente del individio
    for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

        CN_X_i = current_population_vector[ind].getComponents()[component_i];

        CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
        CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
        CN_X_pbest = pbest_individual_components[component_i];

        value = CN_X_i + F * (CN_X_i - CN_X_pbest  + CN_X_r1 - CN_X_r2);

        ind_to_return.setComponent(component_i, value);
    }

    return ind_to_return;
}




//TODO to be tested
Population mutate_RAM_JAPDE(Population current_population, vector<int> mutation_vector, double p) {
    Population offspring = Population(current_population.getPopulationSize());
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector;


    for (int idx = 0; idx < current_population.getPopulationSize(); idx++) {
        offspring_vector.insert(offspring_vector.end(), Individual());
    }
    MutationFunctions mutation_functions_ram_japde[] {
        DE_PBest_1_ind,
        DE_currentToPBest_1_ind
    };

    for (int ind = 0; ind < current_population.getPopulationSize(); ind++) {
    // SELECTION OF MUTATION DEPENDING ON THE NUMBER
    offspring_vector[ind] = mutation_functions_ram_japde[mutation_vector[ind]](current_population_vector, ind, p);
    offspring_vector[ind].setGroup(current_population.getIndividual(ind).getGroup());
    }

    offspring.setIndividuals(offspring_vector);
    offspring.recalculateFitness();
    return offspring;

}

int wheel_roulette(vector<double> probabilities, double max_prob_of_group) {
//Create a reandom and loop over the array of probabilities until findin the corrent number

    double random_value;
    double accumulated_probability;
    int mutation_strategy;


    random_value = (double) rand() / RAND_MAX;
    random_value = 0 + random_value * (max_prob_of_group - 0);

    accumulated_probability = 0;
    mutation_strategy = probabilities[0];

    while (random_value > accumulated_probability or mutation_strategy > probabilities.size()) {
        accumulated_probability = accumulated_probability + probabilities[mutation_strategy];
        mutation_strategy += 1;
    }

    return mutation_strategy - 1;
}

vector<int> selectMutationStrategy(MutationProbabilityTable mutation_probability_table, int number_of_individuals, Population current_population) {
    vector<int> mutation_to_use_vector(number_of_individuals, -1);
    int group = -1;
    vector<double> probability_of_the_group(mutation_probability_table.getNumberOfGroups(), 0);
    double max_prob_of_the_group;

    //for each individual


    //obtenemos el individuo
    for (int individual = 0; individual < mutation_to_use_vector.size(); individual++) {
        // mirar a que grupo pertenece
        // coger el vector de probabilidades del grupo

        //group = ceil(individual / GROUP_SIZE);

        group = current_population.getIndividual(individual).getGroup();
        max_prob_of_the_group = mutation_probability_table.getAccumulatedProbabilityFromGroup(group);
        probability_of_the_group = mutation_probability_table.getProbabilityFromGroup(group);
        mutation_to_use_vector[individual] = wheel_roulette(probability_of_the_group, max_prob_of_the_group);


    }
    return mutation_to_use_vector;

}

vector<double> selectMeanCRValues(TableFandCR table_mean_values, int number_of_individuals, Population current_population) {
    vector<int> mutation_to_use_vector(number_of_individuals, -1);
    vector<double> probability_of_the_cr(TableFandCR::AMOUNT_OF_POSSIBLE_F, 0);

    double max_prob_of_the_group;

    //for each individual


    //obtenemos el individuo
    for (int individual = 0; individual < mutation_to_use_vector.size(); individual++) {
        // mirar a que grupo pertenece
        // coger el vector de probabilidades del grupo


        max_prob_of_the_Cr = table_mean_values.getAccumulatedProbabilityFromRow()

        max_prob_of_the_group = mutation_probability_table.getAccumulatedProbabilityFromGroup(group);
        probability_of_the_cr = mutation_probability_table.getProbabilityFromGroup(cr);
        mutation_to_use_vector[individual] = wheel_roulette(probability_of_the_group, max_prob_of_the_group);


    }
    return mutation_to_use_vector;

}

vector<double> selectMeanFValues(TableFandCR table_mean_values, int number_of_individuals, Population current_population, vector<double> mean_cr_values) {
    vector<int> mutation_to_use_vector(number_of_individuals, -1);
    int group = -1;
    vector<double> probability_of_the_group(mutation_probability_table.getNumberOfGroups(), 0);
    double max_prob_of_the_group;

    //for each individual


    //obtenemos el individuo
    for (int individual = 0; individual < mutation_to_use_vector.size(); individual++) {
        // mirar a que grupo pertenece
        // coger el vector de probabilidades del grupo

        //group = ceil(individual / GROUP_SIZE);

        group = current_population.getIndividual(individual).getGroup();
        max_prob_of_the_group = mutation_probability_table.getAccumulatedProbabilityFromGroup(group);
        probability_of_the_group = mutation_probability_table.getProbabilityFromGroup(group);
        mutation_to_use_vector[individual] = wheel_roulette(probability_of_the_group, max_prob_of_the_group);


    }
    return mutation_to_use_vector;

}

void updateTriesAndSuccessMutTable(Population current_population, Population offspring, MutationProbabilityTable *mutation_probability_table,
                           vector<int> mutation_strategy_to_use, int number_of_function) {
    int group;
    for (int ind = 0; ind < current_population.getPopulationSize(); ind++) {
        group = current_population.getIndividual(ind).getGroup();
        mutation_probability_table->addTries(group, mutation_strategy_to_use[ind], 1);
        if (offspring.getIndividual(ind).betterFitnessThan(current_population.getIndividual(ind), number_of_function)) {
            mutation_probability_table->addSuccess(group, mutation_strategy_to_use[ind], 1);

        }
    }
}

//TODO check if it works

void updateTriesAndSuccessMeanValuesCRF(Population current_population, Population offspring, TableFandCR *mean_values_cr_f,
                                        vector<double>mean_values_cr, vector<double>mean_values_f, int number_of_function) {

    for(int ind = 0; ind < current_population.getPopulationSize(); ind++) {
        mean_values_cr_f->addTries(mean_values_cr[ind]*10, mean_values_f[ind]*10, 1);
        if (offspring.getIndividual(ind).betterFitnessThan(current_population.getIndividual(ind), number_of_function)) {
            mean_values_cr_f->addSuccess(mean_values_cr[ind]*10, mean_values_f[ind]*10, 1);
        }
    }
}


vector<double> calculateCECFitness(Population current_population, int dimension, int population_size, int number_of_function) {
    vector<double> fitness_vector(population_size, 0);
    rowvec fitness;
    fitness = ones<rowvec>(population_size);
    //cout << fitness;
    mat mat_population = Population::populationToMat(current_population);
    cec14_test_func(mat_population.memptr(), fitness.memptr(), dimension, population_size, number_of_function);
    for (int i = 0; i < population_size; i++) {
        fitness_vector[i] = fitness(i);
    }

    //cout << fitness;
    return fitness_vector;


}

bool isOptimumIndividualFound(Population population_to_evaluate, int number_of_function) {
    if ((population_to_evaluate.bestIndividual().getErrorToOptimum(number_of_function)) > EPSILON)
        return false;
    return true;
}


/*
 * Inicializar poblacion con valores de -100 a 100
 * Calcular fitness
 * Iterar hasta que se consigan el máximo de Iteraciones o arrives to the optimum value
     * hacer mutación
     * hacer crossover
     * Calculcar fitness
     * hacer selección
     * print best individual
 *
 */

int newPopulationSize(int number_of_fit_eva) {
    double new_population_size_double;
    int new_population_size;

    double init_minus_min = (double)(Population::POPULATION_SIZE_INIT - Population::POPULATION_SIZE_MIN);
    double division = (double)(((double)number_of_fit_eva)/(MAX_FITNESS_EVALUATIONS));
    new_population_size_double = Population::POPULATION_SIZE_INIT - division * init_minus_min;
    new_population_size = round(new_population_size_double);
    if (new_population_size < Population::POPULATION_SIZE_MIN) {
        return 4;
    }
    return new_population_size;
}

//TODO PROBLEMA DE MIN
int numberOfIndividualsToReduce(Population current_population, int new_population_size) {
    int individuals_to_reduce;
    individuals_to_reduce = current_population.getPopulationSize() - new_population_size;
    return individuals_to_reduce;
}


double calculateP(int evaluations_done, int population_size) {
    double p = 0;
    double first_part = 0;
    double second_part = 0;

    first_part = (1 - ((double)evaluations_done/ MAX_FITNESS_EVALUATIONS));
    second_part = 1/(double)Population::POPULATION_SIZE_INIT;
    p = max(first_part, second_part);
    return p;

}


int main() {



    //srand((unsigned) time(0));

    int number_of_function = 2;
    int number_of_fit_eva = 0;

    double p = 0;

    double eva_maxeva_ratio = 0.0;

    //inicializar población

    cout << "INICIALIZAMOS LA POBLACION";

    Population current_population, mutated_population, offspring = Population();
    vector<Individual> current_population_vector, mutated_population_vector, offspring_vector;
    //current_population = FileReader::setPopulationIndividualsFromFile();

    current_population = Population::initializePopulation(UPPER_BOUND, LOWER_BOUND);
    mat mat_current_population = Population::populationToMat(current_population);
    //inicializar parametros

    vector<double> fitness_vector;
    fitness_vector = calculateCECFitness(current_population, Individual::DIMENSION, current_population.getPopulationSize(), number_of_function);
    number_of_fit_eva += fitness_vector.size();
    current_population.assignFitness(fitness_vector);

    cout << "Su media de Fitness respecto al optimo";
    cout << current_population.calculateMeanErrorToOptimumPopulation(number_of_function);

    current_population.assignGroupToIndividuals(GROUP_SIZE_INIT);



    vector<double> mean_cr_values (current_population.getPopulationSize(), -1);
    vector<double> mean_f_values (current_population.getPopulationSize(), -1);

    TableFandCR mean_cr_f_values = TableFandCR();


    vector<int> mutation_strategy_to_use (current_population.getPopulationSize(), -1);

    // Crear la tabla de mutacion
    MutationProbabilityTable mutation_probability_table = MutationProbabilityTable(GROUP_SIZE_INIT, EVAPORATION_RATE);



    int iteration = 1;
    while (number_of_fit_eva < MAX_FITNESS_EVALUATIONS && !isOptimumIndividualFound(current_population, number_of_function)) {
        p = calculateP(number_of_fit_eva, current_population.getPopulationSize());

        eva_maxeva_ratio = ((double)number_of_fit_eva/ MAX_FITNESS_EVALUATIONS);

        mean_cr_values = selectMeanCRValues( mean_cr_f_values, current_population.getPopulationSize(), current_population);
        mean_f_values = selectMeanFValues(mean_cr_f_values, current_population.getPopulationSize(), current_population, mean_cr_values);

        mutation_strategy_to_use = selectMutationStrategy(mutation_probability_table, current_population.getPopulationSize(), current_population);
        //cout << "\n2.MUTATE THE POPULATION " << "\n";
        mutated_population = mutate_RAM_JAPDE(current_population, mutation_strategy_to_use, p);

        //cout << "\n 3.DO CROSSOVER" << "\n";
        offspring = crossover(current_population, mutated_population);


        fitness_vector = calculateCECFitness(offspring, Individual::DIMENSION, current_population.getPopulationSize(), number_of_function);
        number_of_fit_eva += fitness_vector.size();
        offspring.assignFitness(fitness_vector);
        //cout << "Diff to the optimum of the offspring : " << offspring.calculateMeanErrorToOptimumPopulation(number_of_function);

        //cout << "\n Store Tries and Success" << "\n";

        //cout << "\n 4.DO SELECTION" << "\n";
        for (int ind_to_assign_group = 0; ind_to_assign_group < current_population.getPopulationSize(); ind_to_assign_group++) {
            offspring.setGroupToInd(ind_to_assign_group, current_population.getIndividual(ind_to_assign_group).getGroup());
        }
        updateTriesAndSuccessMutTable(current_population, offspring, &mutation_probability_table, mutation_strategy_to_use, number_of_function);
        updateTriesAndSuccessMeanValuesCRF(current_population, offspring, &mean_cr_f_values, mean_cr_values, mean_f_values, number_of_function);



        current_population = selection(current_population, offspring, number_of_function);
        //cout << " \n AFTER SELECTION \n";



        if (iteration % 2 == 0) {
            cout << "\n ---------iteration " << iteration << "    diff to the optimum de la poblacion:     "
                 << current_population.calculateMeanErrorToOptimumPopulation(number_of_function) << "\n";
            cout << "\n Fitness Evaluations done to the moment:    " << number_of_fit_eva;
            cout << "\nBest individual of the population diff to the optimum:   "
                 << current_population.bestIndividual().getErrorToOptimum(number_of_function);
            cout << "\n" << ((double)number_of_fit_eva/MAX_FITNESS_EVALUATIONS) * 100 << " %" ;

        }

        if (iteration == 833) {
            cout << "asdf";
        }
        if (number_of_fit_eva > 18000){
            cout << "asdf";
            p = calculateP(number_of_fit_eva, current_population.getPopulationSize());
        }

        // si es LP_RAM actualizamos
        if ((iteration % LP_RAM) == 0) {
            mutation_probability_table.updateTable();
            mean_cr_f_values.updateTable();
        }

        // Mirar en cuanto se reduce la poblacion
        int new_population_size = newPopulationSize(number_of_fit_eva);
        int number_of_ind_to_reduce = numberOfIndividualsToReduce(current_population, new_population_size);
        // Mirar que individuos reducir y reducir la poblacion
        current_population.reducePopulation(number_of_ind_to_reduce);

        iteration += 1;



    }
    cout << "\n ---------iteration " << iteration << "    diff to the optimum de la poblacion:     "
         << current_population.calculateMeanErrorToOptimumPopulation(number_of_function) << "\n";
    cout << "\n Fitness Evaluations done to the moment:    " << number_of_fit_eva;
    cout << "\nBest individual of the population diff to the optimum:   "
         << current_population.bestIndividual().getErrorToOptimum(number_of_function);





    //while iterations to be done


    // seleccion de una mutation strategy para cada individuo
    //mutation
    // selection
    //update success and tries
    //if the learning period is finished
    //update probabilities









    return 0;
}
