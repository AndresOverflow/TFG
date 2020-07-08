//
// Created by Andres Ramos on 10/05/2020.
//

#include "individual.h"
#include <iostream>
using namespace std;

// Constructor
Individual::Individual(double fitness) {
    this->fitness = fitness;
    this->vector = {0,0,0,0,0};
    cout << "Object is being created, length = " << fitness << endl;


}

static void InitializeRandomly(Individual ind) {
    cout << "intialized";
}
// Vector value related

void Individual::setVector( std::vector<double> &vector2) {
    std::vector<double>::iterator it;
    it = vector2.begin();
    this->vector.assign(it, vector2.end());
}
vector<double> Individual::getVector(void) {
    return this->vector;
}


// component from the vector related

double Individual::getComponent(int index) {
    return this->vector.at(index);
}
void Individual::setComponent(double value, int index) {
    this->vector.at(index) = value;

}


// fitness value related

double Individual::getFitness( void) {
    return this->fitness;
}

void Individual::setFitness(double fitness){
    this->fitness = fitness;
}


std::string tString(void) {
    std::string string;
    string = "asdff";

    return  string;
};

