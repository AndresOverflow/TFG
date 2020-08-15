//
// Created by Andres Ramos on 08/08/2020.
//

#ifndef UNTITLED1_MUTATIONPROBABILITYTABLE_H
#define UNTITLED1_MUTATIONPROBABILITYTABLE_H

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <altivec.h>
#include "TripletPST.h"

using namespace std;

class MutationProbabilityTable {




public:
    static const int MUTATION_STRATEGIES = 5;
    MutationProbabilityTable();
    void updateTable();
    vector<vector<double>> getTableOfProbabilities();
    int getNumberOfGroups();
    void setNumberOfGroups(int number_of_groups);
    int getNumberOfElementsPerGroup();
    void setNumberOfElementsPerGroup(int number_of_elements_per_group);
    double getProbability(int group, int element);




private:
    int number_of_groups = 0;
    int number_of_elements_per_group = 0;

    vector<vector<TripletPST>> table_of_probabilities;


};


#endif //UNTITLED1_MUTATIONPROBABILITYTABLE_H
