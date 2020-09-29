//
// Created by Andres Ramos on 08/08/2020.
//

#ifndef DE_RAM_JAPDE_CEC14_LSPR_MUTATIONPROBABILITYTABLE_H
#define DE_RAM_JAPDE_CEC14_LSPR_MUTATIONPROBABILITYTABLE_H

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
    static const int MUTATION_STRATEGIES = 2;


    MutationProbabilityTable(int group_size, double evaporation);

    void updateTable(void);

    int getNumberOfGroups(void);

    void addTries(int group, int mutation_str, int tries_to_add);

    void addSuccess(int group, int mutation_str, int success_to_add);

    vector<double> getProbabilityFromGroup(int group);

    double getAccumulatedProbabilityFromGroup(int group);

    void resetTripletsKeepProbabilities();


private:
    double evaporation_rate = 0;
    int number_of_mutation_strategies = 0;
    int number_of_groups;

    vector<vector<TripletPST>> table_of_triplets;


};


#endif //DE_RAM_JAPDE_CEC14_LSPR_MUTATIONPROBABILITYTABLE_H
