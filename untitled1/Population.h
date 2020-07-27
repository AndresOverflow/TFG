//
// Created by Andres Ramos on 09/07/2020.
//

#ifndef UNTITLED1_POPULATION_H
#define UNTITLED1_POPULATION_H

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include "Individual.h"

using namespace std;




class Population {

public:

    static const int POPULATION_SIZE = 5;

    Population(void);

    vector<Individual> getIndividuals(void);
    void setIndividuals(vector<Individual> to_set_population);

    string toString(void);
    Individual bestIndividual(void);




private:
    vector<Individual> individuals;


};


#endif //UNTITLED1_POPULATION_H
