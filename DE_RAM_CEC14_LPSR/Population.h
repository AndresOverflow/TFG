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

    static const int POPULATION_SIZE_INIT = 10;
    static const int POPULATION_SIZE_MIN = 4;

    Population(void);
    Population(int population_size);

    vector<Individual> getIndividuals(void);

    void setIndividuals(vector<Individual> to_set_population);

    Individual getIndividual(int position);

    void setIndividual(int position, Individual ind);

    int getPopulationSize(void);

    void setPopulationSize(int);

    void toString(void);

    Individual bestIndividual(void);

    int WorstIndividualPosition(void);

    void removeIndividual(int pos);

    void recalculateFitness(void);

    double calculateMeanErrorToOptimumPopulation(int function_number);

    void assignFitness(vector<double> fitness_vector);


    void reducePopulation(int number_of_ind_to_reduce);


    static Population initializePopulation(int upper_bound, int lower_bound) {
        Population population_to_return = Population();
        vector<Individual> random_individuals(POPULATION_SIZE_INIT, Individual());
        double random_value;
        for (int i = 0; i < POPULATION_SIZE_INIT; i++) {
            for (int j = 0; j < Individual::DIMENSION; j++) {
                random_value = (double) rand() / RAND_MAX;
                random_value = lower_bound + random_value * (upper_bound - lower_bound);
                random_individuals[i].setComponent(j, random_value);

            }
        }

        population_to_return.setIndividuals(random_individuals);

        return population_to_return;
    }


    //Posible problem of leaking RAM
    static mat populationToMat(Population population_to_transform) {
        mat mat_population = zeros(Individual::DIMENSION, population_to_transform.getPopulationSize());
        for (int ind = 0; ind < population_to_transform.getPopulationSize(); ind++) {
            for (int dim = 0; dim < Individual::DIMENSION; dim++) {
                mat_population(dim, ind) = population_to_transform.getIndividual(ind).getComponent(dim);
            }
        }

        //cout << mat_population;
        return mat_population;
    }


//TODO: mirar el proper size para population_to_create
    static Population matToPopulation(mat matrix) {
        Population population_to_create = Population();
        Individual individual_to_create = Individual();
        for (int ind = 0; ind < population_to_create.getPopulationSize(); ind++) {
            for (int dim = 0; dim < Individual::DIMENSION; dim++) {
                individual_to_create = population_to_create.getIndividual(ind);
                individual_to_create.setComponent(dim, matrix(dim, ind));
                population_to_create.setIndividual(ind, individual_to_create);

            }
        }
        return population_to_create;
    }


private:
    vector<Individual> individuals;
    int population_size;


};


#endif //DE_RAM_CEC14_POPULATION_H
