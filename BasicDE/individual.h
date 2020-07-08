//
// Created by Andres Ramos on 10/05/2020.
//

#ifndef BASICDE_INDIVIDUAL_H
#define BASICDE_INDIVIDUAL_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;



class Individual {

public:
    static const int DIMENSION = 5;

    static void InitializeRandomly(Individual ind);

    void setVector(vector<double> &vector2);
    vector<double> getVector();

    double getComponent(int index);
    void setComponent(double value, int index);

    double getFitness();
    void setFitness(double fitness);

    Individual(double fitness);  // This is the constructor

    std::string tString(void);

private:
    vector<double> vector;
    double fitness;
};


#endif //BASICDE_INDIVIDUAL_H
