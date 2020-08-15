#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Individual.h"
#include "Population.h"
#include "FileReader.h"

using namespace std;

static const double F = 1.7; //mutate factor
static const double CR = 0.15; //Crossover factor
static const int ITERATIONS = 1000;





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
    vector<Individual> mutated_population_vector = mutated_population.getIndividuals();
    vector<Individual> offspring_vector = offspring.getIndividuals();

    float random_value;
    int j_random;
    double value;

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
    vector<Individual> mutated_vector;
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        mutated_vector.insert(mutated_vector.begin(),Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3;
    double CN_X_r1, CN_X_r2, CN_X_r3;

    double value;

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

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;

}

vector<Individual> DE_rand_2(vector<Individual> current_population_vector) {
    vector<Individual> mutated_vector;
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        mutated_vector.insert(mutated_vector.begin(),Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3, N_X_r4, N_X_r5;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_r4, CN_X_r5;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        N_X_r1 = (rand() % Population::POPULATION_SIZE);
        N_X_r2 = (rand() % Population::POPULATION_SIZE);
        N_X_r3 = (rand() % Population::POPULATION_SIZE);
        N_X_r4 = (rand() % Population::POPULATION_SIZE);
        N_X_r5 = (rand() % Population::POPULATION_SIZE);

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
    Population current_population = Population();
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        mutated_vector.insert(mutated_vector.begin(),Individual());
    }

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_best;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        N_X_r1 = (rand() % Population::POPULATION_SIZE);
        N_X_r2 = (rand() % Population::POPULATION_SIZE);


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
    Population current_population = Population();
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        mutated_vector.insert(mutated_vector.begin(),Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3, N_X_r4;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_r4, CN_X_best;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        N_X_r1 = (rand() % Population::POPULATION_SIZE);
        N_X_r2 = (rand() % Population::POPULATION_SIZE);
        N_X_r3 = (rand() % Population::POPULATION_SIZE);
        N_X_r4 = (rand() % Population::POPULATION_SIZE);


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
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        mutated_vector.insert(mutated_vector.begin(),Individual());
    }

    int N_X_r1, N_X_r2, N_X_r3;
    double CN_X_r1, CN_X_r2, CN_X_r3, CN_X_i;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        N_X_r1 = (rand() % Population::POPULATION_SIZE);
        N_X_r2 = (rand() % Population::POPULATION_SIZE);
        N_X_r3 = (rand() % Population::POPULATION_SIZE);



        //Por cada componente del individio
        for (int component_i = 0; component_i < Individual::DIMENSION; component_i++) {

            CN_X_i = current_population_vector[i].getComponents()[component_i];

            CN_X_r1 = current_population_vector[N_X_r1].getComponents()[component_i];
            CN_X_r2 = current_population_vector[N_X_r2].getComponents()[component_i];
            CN_X_r3 = current_population_vector[N_X_r3].getComponents()[component_i];



            value = CN_X_i+ F * (CN_X_r1 - CN_X_i + CN_X_r2 - CN_X_r3);

            mutated_vector[i].setComponent(component_i, value);
        }
    }

    return mutated_vector;
}

vector<Individual> DE_currentToBest_1(vector<Individual> current_population_vector) {

    vector<Individual> mutated_vector;
    Population current_population = Population();
    current_population.setIndividuals(current_population_vector);
    vector<double> best_individual_components = current_population.bestIndividual().getComponents();
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        mutated_vector.insert(mutated_vector.begin(),Individual());
    }

    int N_X_r1, N_X_r2;
    double CN_X_r1, CN_X_r2, CN_X_i, CN_X_best;

    double value;

    //Por cada individuo de la población
    //escogemos 3 elementos aleatoriamente de la poblacion
    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        N_X_r1 = (rand() % Population::POPULATION_SIZE);
        N_X_r2 = (rand() % Population::POPULATION_SIZE);



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


Population mutate(Population current_population) {

    Population offspring = Population();
    vector<Individual> current_population_vector = current_population.getIndividuals();
    vector<Individual> offspring_vector;
    for (int idx = 0; idx < Population::POPULATION_SIZE; idx++) {
        offspring_vector.insert(offspring_vector.end(), Individual());
    }

    offspring_vector = DE_currentToRandom_1(current_population_vector);

    offspring.setIndividuals(offspring_vector);
    offspring.recalculateFitness();
    return offspring;
}


int main() {


    Population population_to_fill = Population();
    population_to_fill = FileReader::setPopulationIndividualsFromFile();
//    srand((unsigned) time(0));

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

