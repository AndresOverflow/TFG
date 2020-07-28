#include <iostream>
#include <string>
#include <vector>
#include "Individual.h"

using namespace std;

static const int PS = 2;
static const double F = 1.25; //mutate factor
static const double CR = 0.5; //Crossover factor
static const bool BEST_LESS = 1; // 1 if aims for less fitness else 0.


void print(std::vector<Individual> &a) {
    std::cout << "The population individuals are :  \n";

    for (int i = 0; i < a.size(); i++) {
        cout << "Element number " << i << "\n";
        cout << a[i].toString();
    }
}

Individual bestIndividual(vector<Individual> population) {
    Individual best_individual = Individual();
    for (int i = 0; i < PS; i++) {
        if (population[i].getFitness() < best_individual.getFitness()) {
            best_individual.setFitness(population[i].getFitness());
            best_individual.setComponents(population[i].getComponents());
        }
    }

    return best_individual;
}


vector<Individual> selection(vector<Individual> current_population, vector<Individual> offspring) {
    cout << "selection function";
    vector<Individual> final_population = {Individual(), Individual()};

    for (int i = 0; i < PS; i++) {
        if (current_population[i].betterFitnessThan(offspring[i])) {
            final_population[i].setComponents(current_population[i].getComponents());
            final_population[i].setFitness(current_population[i].getFitness());
        } else {
            final_population[i].setComponents(offspring[i].getComponents());
            final_population[i].setFitness(offspring[i].getFitness());
        }
    }
    return final_population;
}


//binomial crossover
vector<Individual> crossover(vector<Individual> current_population, vector<Individual> mutated_population) {
    vector<Individual> offspring = {Individual(), Individual()};

    srand((unsigned) time(0));
    float random_value;
    int j_random, value;


    //por cada individuo de la poblacion
    for (int individual_i = 0; individual_i < PS; individual_i++) {
        //generamos escogemos una componente
        j_random = (random() % PS);
        //por cada componente
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {
            // generar un numero random de 0 a 1
            random_value = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

            // si el numero es menor que CR o es el indice j entonces es la componente mutada
            // si es mayor que CR y no es j entonces es la componente original
            if (random_value <= CR or component_i == j_random) {
                value = mutated_population[individual_i].getComponent(component_i);
                offspring[individual_i].setComponent(component_i, value);
            } else {
                value = current_population[individual_i].getComponent(component_i);
                offspring[individual_i].setComponent(component_i, value);
            }
        }
    }

    cout << "\n crossover \n";
    return offspring;

}


/*
 * realiza la mutación de una población y devuelve el el vector mutado
 */




vector<Individual> DE_rand_1(vector<Individual> current_population) {
    vector<Individual> offspring = {Individual(), Individual()};
    srand((unsigned) time(0));

    int N_X_r1, N_X_r2, N_X_r3, CN_X_r1, CN_X_r2, CN_X_r3;

    int value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < PS; i++) {
        N_X_r1 = (rand() % PS);
        N_X_r2 = (rand() % PS);
        N_X_r3 = (rand() % PS);

        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_r1 = current_population[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population[N_X_r3].getComponents()[component_i];

            value = CN_X_r1 + F * (CN_X_r2 - CN_X_r3);

            offspring[i].setComponent(component_i, value);
        }
    }

    return offspring;

}

vector<Individual> DE_rand_2(vector<Individual> current_population) {
    vector<Individual> offspring = {Individual(), Individual()};
    cout << " DE_rand_2";
    Individual::soemthing();
    return offspring;
}

vector<Individual> DE_best_1(vector<Individual> current_population) {
    vector<Individual> offspring = {Individual(), Individual()};
    cout << " DE_rand_2";
    return offspring;
}

vector<Individual> DE_best_2(vector<Individual> current_population) {
    vector<Individual> offspring = {Individual(), Individual()};
    cout << " DE_rand_2";
    return offspring;
}

vector<Individual> DE_currentToRandom_1(vector<Individual> current_population) {
    vector<Individual> offspring = {Individual(), Individual()};
    cout << " DE_rand_2";
    return offspring;
}

vector<Individual> DE_currentToBest_1(vector<Individual> current_population) {
    vector<Individual> offspring = {Individual(), Individual()};
    cout << " DE_rand_2";
    return offspring;
}


vector<Individual> mutate(vector<Individual> current_population) {
    vector<Individual> offspring;
    for (int idx = 0; idx < PS; idx++) {
        offspring.insert(offspring.end(), Individual(0));
    }

    offspring = DE_rand_1(current_population);
    return offspring;
    cout << "\n mutate \n";
}


int main() {

// 1. Inicializar population
//Hacerlo varias veces
// 2. Hacer mutate de la poblacion
// 3. Hacer crossover
// 4. Hacer la selección del offspring


    vector<Individual> current_population, mutated_population, offspring;
    // Initialize the population


    vector<double> components_ind1 = {1.0, 20.0, 70.0, 3.0, 44.5};
    vector<double> components_ind2 = {3.0, 2.2, 5.3, 1.0, 15.5};

    current_population = {Individual(components_ind1), Individual(components_ind2)};

    cout << "1.INITIALIZE CURRENT POPULATION" << "\n";
    cout << "CURRENT POPULATION" << "\n";
    print(current_population);

    cout << "2.MUTATE THE POPULATION " << "\n";
    mutated_population = mutate(current_population);
    cout << "MUTATED POPULATION" << "\n";
    // Calculate fitness
    for (int individual_i = 0; individual_i < PS; individual_i++) {
        mutated_population[individual_i].setFitness(mutated_population[individual_i].calculate_fitness());
    }

    print(mutated_population);


    cout << "3.DO CROSSOVER" << "\n";
    offspring = crossover(current_population, mutated_population);
    cout << "CROSSOVER POPULATION" << "\n";
     // Calculate fitness
    for (int individual_i = 0; individual_i < PS; individual_i++) {
        offspring[individual_i].setFitness(offspring[individual_i].calculate_fitness());
    }


    print(offspring);


    cout << "4.DO SELECTION" << "\n";


    current_population = selection(current_population, offspring);
    cout << " \n AFTER SELECTION \n";
    print(current_population);


    cout << "\n " << "BEST INDIVIDUAL" << bestIndividual(current_population).toString() << "\n";


    cout << "\n" << "end of the program";
    return 0;

}
