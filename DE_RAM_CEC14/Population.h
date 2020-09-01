//
// Created by Andres Ramos on 09/07/2020.
//

#ifndef DE_RAM_CEC14_POPULATION_H
#define DE_RAM_CEC14_POPULATION_H


#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>


#include "Individual.h"
#include "armadillo.h"

using namespace arma;
using namespace std;




class Population {

public:

    static const int POPULATION_SIZE = 10;

    Population(void);

    vector<Individual> getIndividuals(void);
    void setIndividuals(vector<Individual> to_set_population);

    Individual getIndividual(int position);
    void setIndividual(int position, Individual ind);

    void toString(void);
    Individual bestIndividual(void);

    void recalculateFitness(void);
    double calculateMeanFitnessPopulation(void);

    static Population initializePopulation(int upper_bound, int lower_bound) {
        Population population_to_return = Population();
        vector<Individual> random_individuals  (Population::POPULATION_SIZE, Individual());
        double random_value;
        for (int i = 0; i < Population::POPULATION_SIZE; i++) {
            for (int j = 0; j< Individual::DIMENSION; j++) {
                random_value = (double)rand() / RAND_MAX;
                random_value = lower_bound + random_value * (upper_bound - lower_bound);
                random_individuals[i].setComponent(j, random_value);

            }
        }

        population_to_return.setIndividuals(random_individuals);

        return population_to_return;
    }


    //Posible problem of leaking RAM
    static mat populationToMat(Population population_to_transform) {
    mat mat_population = zeros(Individual::DIMENSION, POPULATION_SIZE);
    for(int ind = 0; ind < POPULATION_SIZE; ind++) {
        for(int dim = 0; dim < Individual::DIMENSION; dim++){
           mat_population(dim,ind) = population_to_transform.getIndividual(ind).getComponent(dim);
        }
    }

    cout << mat_population;
    return mat_population;
}



private:
    vector<Individual> individuals;


};


#endif //DE_RAM_CEC14_POPULATION_H
