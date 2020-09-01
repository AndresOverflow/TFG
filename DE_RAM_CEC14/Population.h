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

    static Population initializePopulation(int upper_bound, int lower_bound);



private:
    vector<Individual> individuals;


};


#endif //DE_RAM_CEC14_POPULATION_H
