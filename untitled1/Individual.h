//
// Created by Andres Ramos on 15/05/2020.
//

#ifndef UNTITLED1_INDIVIDUAL_H
#define UNTITLED1_INDIVIDUAL_H
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>

using namespace std;


class Individual {

public:

    static const int DIMENSION;
    static const bool BEST_LESS = 1; // 1 if aims for less fitness else 0.


    Individual(double fitness);
    Individual(void);
    Individual(vector<double> components_vector);
    double getFitness(void);
    void setFitness(double fitness);

    vector<double> getComponents(void);
    void setComponents(vector<double> vector2);
    void setComponent(int position, double value);
    double getComponent(int position);

    string toString(void);

    double calculate_fitness();
    bool betterFitnessThan(Individual compare_to_individual);



private:
    double fitness;
    vector<double> components;

};


#endif //UNTITLED1_INDIVIDUAL_H
