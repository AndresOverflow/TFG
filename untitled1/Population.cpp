//
// Created by Andres Ramos on 09/07/2020.
//

#include "Population.h"

const int Population::POPULATION_DIMENSION;

//constructor

Population::Population() {
    for (int i = 0 ; i < POPULATION_DIMENSION; i++) {
       this->individuals.insert(this->individuals.begin(),Individual());
    }

}

vector<Individual> Population::getIndividuals() {

}

void Population::setIndividuals(vector<Individual> to_set_population) {
    vector<Individual>::iterator it;
    it = to_set_p.begin();

    this->components.assign(it, vector2.end());

}
Individual::Individual(void) {
    this->fitness = 10;
    this->components = {0,0,0,0,0};
}

// fitness
double Individual::getFitness() {
    return this->fitness;
}

void Individual::setFitness(double fitness) {
    this->fitness = fitness;
}

vector<int> Individual::getComponents(void) {
    return this->components;
}

void Individual::setComponents(vector<int> vector2) {
    vector<int>::iterator it;
    it = vector2.begin();

    this->components.assign(it,vector2.end());

}

string Individual::toString(void) {
    string result = "------------------ \n";
    result.append( "Fitness:");
    result.append(to_string(fitness));
    result.append("\n");
    for( int i = 0; i < this->components.size(); i++ ){

        result.append("Component ");
        result.append(to_string(i));
        result.append(" : ");
        result.append(to_string(this->components[i]));
        result.append("\n");
    }

    result.append("------------------ \n");
    return result;
}

double Individual::calculate_fitness() {
    double aim = 10;
    double diff = 0;
    for (int &i: Individual::components) {
        diff = diff + abs(aim - i);
    }
    return diff;

}

bool Individual::betterFitnessThan(Individual individual_to_compare) {
    bool result;
    if(this->getFitness() < individual_to_compare.getFitness()) {
        result = true;
    } else {
        result = false;
    }
    if(BEST_LESS == 0) {
        result = !result;
    }

    return result;

}
