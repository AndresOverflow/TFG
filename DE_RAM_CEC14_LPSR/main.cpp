#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Individual.h"
#include "Population.h"
#include "FileReader.h"
#include "MutationProbabilityTable.h"
#include "armadillo.h"

//TODO raro que el bestIndividual siempre sea el mismo al principio



void cec14_test_func(double *, double *, int, int, int);

double *OShift, *M, *y, *z, *x_bound;
int ini_flag = 0, n_flag, func_flag, *SS;

using namespace std;
using namespace arma;

//static const double F = 1.7; //mutate factor
static const double F = 0.7; //mutate factor
static const double CR = 0.15; //Crossover factor
//static const double CR = 0.15; //Crossover factor
static const int GROUP_SIZE = 5;
static const double EVAPORATION_RATE = 0.2;
static const int LP_RAM = 100;
static const int UPPER_BOUND = 100;
static const int LOWER_BOUND = -100;
const double EPSILON = pow(10.0, -8);
const int MAX_FITNESS_EVALUATIONS = Population::POPULATION_SIZE_INIT * 10000;

typedef Individual (*MutationFunctions)(vector<Individual> current_population, int ind);


//TODO: Question, mutation table with probabilities that sum more that 1?
//TODO: Question, cuantas fitness operations? porque para hacer la mutacion también los calculo



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
            } else {
                value = current_population_vector[individual_i].getComponent(component_i);
                offspring_vector[individual_i].setComponent(component_i, value);
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


Population mutate(Population current_population) {

    Population offspring = Population();
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector;
    for (int idx = 0; idx < current_population.getPopulationSize(); idx++) {
        offspring_vector.insert(offspring_vector.end(), Individual());
    }

    offspring_vector = DE_currentToRandom_1(current_population_vector);

    offspring.setIndividuals(offspring_vector);
    offspring.recalculateFitness();
    return offspring;
}

Population mutate_RAM(Population current_population, vector<int> mutation_vector) {
    Population offspring = Population(current_population.getPopulationSize());
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector;

    MutationFunctions mutation_functions_ram[] = {

            DE_rand_1_ind,
            DE_rand_2_ind,
            DE_best_1_ind,
            DE_best_2_ind,
            DE_currentToRandom_1_ind

    };
    for (int idx = 0; idx < current_population.getPopulationSize(); idx++) {
        offspring_vector.insert(offspring_vector.end(), Individual());
    }

    for (int ind = 0; ind < current_population.getPopulationSize(); ind++) {
        // SELECTION OF MUTATION DEPENDING ON THE NUMBER
        offspring_vector[ind] = mutation_functions_ram[mutation_vector[ind]](current_population_vector, ind);
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

vector<int> selectMutationStrategy(MutationProbabilityTable mutation_probability_table, int number_of_individuals) {
    vector<int> mutation_to_use_vector(number_of_individuals, -1);
    int group = -1;
    vector<double> probability_of_the_group(mutation_probability_table.getNumberOfGroups(), 0);
    double max_prob_of_the_group;

    //for each individual


    for (int individual = 0; individual < mutation_to_use_vector.size(); individual++) {
        // mirar a que grupo pertenece
        // coger el vector de probabilidades del grupo

        group = ceil(individual / GROUP_SIZE);
        max_prob_of_the_group = mutation_probability_table.getAccumulatedProbabilityFromGroup(group);
        probability_of_the_group = mutation_probability_table.getProbabilityFromGroup(group);
        mutation_to_use_vector[individual] = wheel_roulette(probability_of_the_group, max_prob_of_the_group);


    }
    return mutation_to_use_vector;

}

void updateTriesAndSuccess(Population current_population, Population offspring, MutationProbabilityTable *mutation_probability_table,
                           vector<int> mutation_strategy_to_use, int number_of_function) {
    int group;
    for (int ind = 0; ind < current_population.getPopulationSize(); ind++) {
        group = ceil(ind / GROUP_SIZE);
        mutation_probability_table->addTries(group, mutation_strategy_to_use[ind], 1);
        if (offspring.getIndividual(ind).betterFitnessThan(current_population.getIndividual(ind), number_of_function)) {
            mutation_probability_table->addSuccess(group, mutation_strategy_to_use[ind], 1);

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
    int new_population_size;

    double init_minus_min = (double)(Population::POPULATION_SIZE_INIT - Population::POPULATION_SIZE_MIN);
    double division = (double)(((double)number_of_fit_eva)/(MAX_FITNESS_EVALUATIONS));
    new_population_size = round(Population::POPULATION_SIZE_INIT - division * init_minus_min);
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

int main() {

    //srand((unsigned) time(0));

    int number_of_function = 2;
    int number_of_fit_eva = 0;


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

    vector<int> mutation_strategy_to_use (current_population.getPopulationSize(), -1);

    // Crear la tabla de mutacion
    MutationProbabilityTable mutation_probability_table = MutationProbabilityTable(GROUP_SIZE, EVAPORATION_RATE);

    int iteration = 1;
    while (number_of_fit_eva < MAX_FITNESS_EVALUATIONS && !isOptimumIndividualFound(current_population, number_of_function)) {
        mutation_strategy_to_use = selectMutationStrategy(mutation_probability_table, current_population.getPopulationSize());
        //cout << "\n2.MUTATE THE POPULATION " << "\n";
        mutated_population = mutate_RAM(current_population, mutation_strategy_to_use);

        //cout << "\n 3.DO CROSSOVER" << "\n";
        offspring = crossover(current_population, mutated_population);


        fitness_vector = calculateCECFitness(offspring, Individual::DIMENSION, current_population.getPopulationSize(), number_of_function);
        number_of_fit_eva += fitness_vector.size();
        offspring.assignFitness(fitness_vector);
        //cout << "Diff to the optimum of the offspring : " << offspring.calculateMeanErrorToOptimumPopulation(number_of_function);

        //cout << "\n Store Tries and Success" << "\n";

        //cout << "\n 4.DO SELECTION" << "\n";
        updateTriesAndSuccess(current_population, offspring, &mutation_probability_table, mutation_strategy_to_use, number_of_function);


        current_population = selection(current_population, offspring, number_of_function);
        //cout << " \n AFTER SELECTION \n";



        if (iteration % 10 == 0) {
            cout << "\n ---------iteration " << iteration << "    diff to the optimum de la poblacion:     "
                 << current_population.calculateMeanErrorToOptimumPopulation(number_of_function) << "\n";
            cout << "\n Fitness Evaluations done to the moment:    " << number_of_fit_eva;
            cout << "\nBest individual of the population diff to the optimum:   "
                 << current_population.bestIndividual().getErrorToOptimum(number_of_function);

        }

        if (iteration == 2000) {
            cout << "asdf";
        }

        // si es LP_RAM actualizamos
        if ((iteration % LP_RAM) == 0) {
            mutation_probability_table.updateTable();
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

/*

int main2() {
    int number_of_function = 1;

// 1. Inicializar population
//Hacerlo varias veces
// 2. Hacer mutate de la poblacion
// 3. Hacer crossover
// 4. Hacer la selección del offspring

    double difference_mean_improvement = 0;

    Population current_population, mutated_population, offspring = Population();

    vector<Individual> current_population_vector, mutated_population_vector, offspring_vector;
    // Initialize the population

    current_population = FileReader::setPopulationIndividualsFromFile();


    cout << "1.INITIALIZE CURRENT POPULATION" << "\n";
    cout << "CURRENT POPULATION" << "\n";
    //current_population.toString();

    difference_mean_improvement = current_population.calculateMeanFitnessPopulation();
    cout << current_population.calculateMeanFitnessPopulation();

    for (int iterations = 0; iterations < ITERATIONS; iterations++) {
        cout << "\n2.MUTATE THE POPULATION " << "\n";
        mutated_population = mutate(current_population);
        cout << "MUTATED POPULATION" << "\n";

        // Calculate fitness

        mutated_population.recalculateFitness();
        cout << mutated_population.calculateMeanFitnessPopulation();

        //mutated_population.toString();


        cout << "\n 3.DO CROSSOVER" << "\n";
        offspring = crossover(current_population, mutated_population);
        cout << "CROSSOVER POPULATION" << "\n";
        //Calculate fitness


        //offspring.toString();
        offspring.recalculateFitness();
        cout << offspring.calculateMeanFitnessPopulation();


        cout << "\n 4.DO SELECTION" << "\n";


        current_population = selection(current_population, offspring);
        cout << " \n AFTER SELECTION \n";
        //current_population.toString();
        difference_mean_improvement -= current_population.calculateMeanFitnessPopulation();

        cout << current_population.calculateMeanFitnessPopulation();

        //cout << "\n " << "BEST INDIVIDUAL" << current_population.bestIndividual().toString() << "\n";
        cout << " \n iteration " << iterations << "    " << current_population.calculateMeanFitnessPopulation() <<  "\n";
    }
    cout << "\n2.MUTATE THE POPULATION " << "\n";
    mutated_population = mutate(current_population);
    cout << "MUTATED POPULATION" << "\n";

    // Calculate fitness

    mutated_population.recalculateFitness();
    cout << mutated_population.calculateMeanFitnessPopulation();

    //mutated_population.toString();


    cout << "\n 3.DO CROSSOVER" << "\n";
    offspring = crossover(current_population, mutated_population);
    cout << "CROSSOVER POPULATION" << "\n";
    //Calculate fitness


    //offspring.toString();
    offspring.recalculateFitness();
    cout << offspring.calculateMeanFitnessPopulation();


    cout << "\n 4.DO SELECTION" << "\n";


    current_population = selection(current_population, offspring);
    cout << " \n AFTER SELECTION \n";
    //current_population.toString();
    difference_mean_improvement -= current_population.calculateMeanFitnessPopulation();

    cout << current_population.calculateMeanFitnessPopulation();

    //cout << "\n " << "BEST INDIVIDUAL" << current_population.bestIndividual().toString() << "\n";
    cout << " \n iteration + +1" << "    " << current_population.calculateMeanFitnessPopulation() <<  "\n";


    cout << "\n" << "end of the program \n";
    return 0;

}

*/