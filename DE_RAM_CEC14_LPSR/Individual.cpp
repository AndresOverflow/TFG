//
// Created by Andres Ramos on 15/05/2020.
//


#include "Individual.h"




//constructor



Individual::Individual(void) {
    this->group = NOT_INITIALIZED_GROUP;
    this->fitness = NOT_INITIALIZED;
    for (int i = 0; i < DIMENSION; i++) {
        this->components.insert(this->components.begin(), 0);
    }
}

Individual::Individual(vector<double> components_vector) {
    vector<double>::iterator it;
    it = components_vector.begin();
    this->components.assign(it, components_vector.end());
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

    this->components.assign(it, vector2.end());

}

string Individual::toString(void) {
    string result = "------------------ \n";
    result.append("Fitness:");
    result.append(to_string(fitness));
    result.append("\n");
    for (int i = 0; i < this->components.size(); i++) {

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

bool Individual::betterFitnessThan(Individual individual_to_compare, int number_of_function) {
    double dif_1, dif_2;
    dif_1 = abs((this->getFitness() - (number_of_function * 100)));
    dif_2 = abs((individual_to_compare.getFitness() - (number_of_function * 100)));
    if (dif_1 < dif_2) {
        return true;
    }
    return false;
}

void Individual::setComponent(int position, double value) {
    this->components[position] = value;

}

double Individual::getComponent(int position) {

    return this->components[position];
}

double Individual::getErrorToOptimum(int function_number) {
    double dif = 0.0;
    dif = abs(this->getFitness() - (function_number * 100));
    return dif;
}

int Individual::getGroup(){
    return this->group;
}

void Individual::setGroup(int group) {
    this->group = group;
}



//TODO static double Individual::minus