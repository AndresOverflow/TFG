//
// Created by Andres Ramos on 09/07/2020.
//

#include "Population.h"


//constructor

Population::Population() {
    for (int i = 0 ; i < POPULATION_SIZE; i++) {
       this->individuals.insert(this->individuals.begin(),Individual());
    }

}

vector<Individual> Population::getIndividuals() {
    return this->individuals;
}

void Population::setIndividuals(vector<Individual> to_set_population) {
    vector<Individual>::iterator it;
    it = to_set_population.begin();

    this->individuals.assign(it, to_set_population.end());

}


