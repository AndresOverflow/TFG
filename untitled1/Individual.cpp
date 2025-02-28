//
// Created by Andres Ramos on 15/05/2020.
//


#include "Individual.h"




//constructor



Individual::Individual(void) {
    this->fitness = NOT_INITIALIZED;
    for (int i = 0 ; i < DIMENSION; i++) {
       this->components.insert(this->components.begin(), 0);
    }
}

Individual::Individual(vector<double> components_vector) {
    vector<double>::iterator it;
    it = components_vector.begin();
    this->components.assign(it,components_vector.end());
    this->fitness = this->calculate_fitness();
}

// fitness
double Individual::getFitness() {
    return this->fitness;
}

void Individual::setFitness(double fitness) {
    this->fitness = fitness;
}

vector<double> Individual::getComponents(void) {
    return this->components;
}

void Individual::setComponents(vector<double> vector2) {
    vector<double>::iterator it;
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
    double aim = 50;
    double diff = 0;
    for (double &i: Individual::components) {
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

void Individual::setComponent(int position, double value) {
    this->components[position] = value;

}

double Individual::getComponent(int position) {

    return this->components[position];
}



//TODO static double Individual::minus