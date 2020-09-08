//
// Created by Andres Ramos on 15/05/2020.
//

#ifndef DE_RAM_CEC14_INDIVIDUAL_H
#define DE_RAM_CEC14_INDIVIDUAL_H

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;


class Individual {

public:

    static const int DIMENSION = 30;
    static const bool BEST_LESS = 1; // 1 if aims for less fitness else 0.
    constexpr static const double NOT_INITIALIZED = 9999.9;


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

    bool betterFitnessThan(Individual compare_to_individual, int number_of_function);

    double getErrorToOptimum(int number_of_function);


private:
    double fitness;
    vector<double> components;

};


#endif //DE_RAM_CEC14_INDIVIDUAL_H
