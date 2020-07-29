#include <iostream>
#include <string>
#include <vector>
#include "Individual.h"
#include "Population.h"

using namespace std;

static const double F = 1.25; //mutate factor
static const double CR = 0.5; //Crossover factor
static const bool BEST_LESS = 1; // 1 if aims for less fitness else 0.




Population selection(Population current_population, Population offspring) {
    Population final_population = Population();
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector = offspring.getIndividuals();


    cout << "selection function";
    //TODO cambiar el numero de individuos en funcion del population size
    vector<Individual> final_population_vector = final_population.getIndividuals();

    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        if (current_population_vector[i].betterFitnessThan(offspring_vector[i])) {
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


//binomial crossover
Population crossover(Population current_population, Population mutated_population) {
    Population offspring = Population();

    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> mutated_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector = offspring.getIndividuals();

    srand((unsigned) time(0));
    float random_value;
    int j_random, value;


    //por cada individuo de la poblacion
    for (int individual_i = 0; individual_i < Population::POPULATION_SIZE; individual_i++) {
        //generamos escogemos una componente
        j_random = (random() % Population::POPULATION_SIZE);
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

    cout << "\n crossover \n";
    return offspring;

}


/*
 * realiza la mutación de una población y devuelve el el vector mutado
 */




vector<Individual> DE_rand_1(vector<Individual> current_population_vector) {
    vector<Individual> offspring_vector;
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        offspring_vector.insert(offspring_vector.begin(),Individual());
    }
    srand((unsigned) time(0));

    int N_X_r1, N_X_r2, N_X_r3, CN_X_r1, CN_X_r2, CN_X_r3;

    int value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        N_X_r1 = (rand() % Population::POPULATION_SIZE);
        N_X_r2 = (rand() % Population::POPULATION_SIZE);
        N_X_r3 = (rand() % Population::POPULATION_SIZE);

        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];

            value = CN_X_r1 + F * (CN_X_r2 - CN_X_r3);

            offspring_vector[i].setComponent(component_i, value);
        }
    }

    return offspring_vector;

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


Population mutate(Population current_population) {

    Population offspring = Population();
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector;
    for (int idx = 0; idx < Population::POPULATION_SIZE; idx++) {
        offspring_vector.insert(offspring_vector.end(), Individual());
    }

    offspring_vector = DE_rand_1(current_population_vector);

    offspring.setIndividuals(offspring_vector);
    offspring.recalculateFitness();
    return offspring;
    cout << "\n mutate \n";
}


int main() {






// 1. Inicializar population
//Hacerlo varias veces
// 2. Hacer mutate de la poblacion
// 3. Hacer crossover
// 4. Hacer la selección del offspring

    Population current_population, mutated_population, offspring = Population();

    vector<Individual> current_population_vector, mutated_population_vector, offspring_vector;
    // Initialize the population


    vector<double> components_ind1 = {1.0, 20.0, 70.0, 3.0, 44.5, 6.9, 50.0, 10.0, 7.0, 100.0};
    vector<double> components_ind2 = {3.0, 2.2, 5.3, 1.0, 15.5, 70, 80, 20, 100, 500};
    vector<double> components_ind3 = {1.0, 600.0, 200.0, 3.0, 800.5, 6.9, 50.0, 10.0, 7.0, 10100.0};
    vector<double> components_ind4 = {1.0, 70.0, 750.0, 3.0, 44.5, 60.9, 50.0, 100.0, 7.0, 1005.0};
    vector<double> components_ind5 = {1.0, 2000.0, 700.0, 33.0, 445.5, 6.9, 50.0, 10.0, 7.0, 1020.0};

    current_population.setIndividuals({Individual(components_ind1), Individual(components_ind2), Individual(components_ind3), Individual(components_ind4),Individual(components_ind5)});


    cout << "1.INITIALIZE CURRENT POPULATION" << "\n";
    cout << "CURRENT POPULATION" << "\n";
    current_population.toString();


    cout << "2.MUTATE THE POPULATION " << "\n";
    mutated_population = mutate(current_population);
    cout << "MUTATED POPULATION" << "\n";

    // Calculate fitness

    mutated_population.recalculateFitness();

    mutated_population.toString();


    cout << "3.DO CROSSOVER" << "\n";
    offspring = crossover(current_population, mutated_population);
    cout << "CROSSOVER POPULATION" << "\n";
    //Calculate fitness


    offspring.toString();


    cout << "4.DO SELECTION" << "\n";


    current_population = selection(current_population, offspring);
    cout << " \n AFTER SELECTION \n";
    current_population.toString();


    cout << "\n " << "BEST INDIVIDUAL" << current_population.bestIndividual().toString() << "\n";


    cout << "\n" << "end of the program";
    return 0;

}

