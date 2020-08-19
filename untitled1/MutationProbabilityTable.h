//
// Created by Andres Ramos on 08/08/2020.
//

#ifndef UNTITLED1_MUTATIONPROBABILITYTABLE_H
#define UNTITLED1_MUTATIONPROBABILITYTABLE_H

#include "TripletPST.h"
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <iostream>


#include "Population.h"

using namespace std;

class MutationProbabilityTable {




public:
    static const int MUTATION_STRATEGIES = 5;



    MutationProbabilityTable(int group_size, double evaporation);
    void updateTable(void);
    //vector<vector<TripletPST>> getTableOfProbabilities(void);
    int getNumberOfGroups(void);
    void setNumberOfGroups(int number_of_groups);
    int getNumberOfElementsPerGroup();
    void setNumberOfElementsPerGroup(int number_of_elements_per_group);
    double getProbability(int group, int mutation_str);
    void addTries(int group, int mutation_str, int tries_to_add);
    void addSuccess(int group, int mutation_str, int success_to_add);





private:
    double evaporation_rate = 0;
    int number_of_mutation_strategies = 0;
    int number_of_groups;

   vector<vector<TripletPST>> table_of_triplets;






};


#endif //UNTITLED1_MUTATIONPROBABILITYTABLE_H
