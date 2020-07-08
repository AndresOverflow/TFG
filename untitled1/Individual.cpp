//
// Created by Andres Ramos on 15/05/2020.
//


#include "Individual.h"



const int Individual::DIMENSION = 4;

//constructor

Individual::Individual(double fitness) {
    this->fitness = fitness;
    this->components = {1,2,3,4,5};
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

//TODO static double Individual::minus