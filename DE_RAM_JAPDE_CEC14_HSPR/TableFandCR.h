//
// Created by Andres Ramos on 17/09/2020.
//

#ifndef DE_RAM_JAPDE_CEC14_LSPR_TABLEFANDCR_H
#define DE_RAM_JAPDE_CEC14_LSPR_TABLEFANDCR_H

#include "TripletPST.h"
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

class TableFandCR {

public:
    constexpr static const double EPA = 0.05;
    static const int AMOUNT_OF_POSSIBLE_F = 11;
    static const int AMOUNT_OF_POSSIBLE_CR = 11;

    TableFandCR(void);

    void updateTable(double eva_maxeva_ratio);



    vector<double> getProbabilityFromRow(int row);
    vector<double> getProbabilityFromCol(int col);
    double getAccumulatedProbabilityFromRow(int row);
    double getAccumulatedProbabilityFromCol(int col);

    double getProbabilityFromElement(int cr, int f);

    double incrementMcrf(int rowCr, int colF, double eva_maxeva_ratio);
    double EPf(int val_f, double eva_maxeva_ratio);

    void addTries(int cr, int f, int tries_to_add);
    void addSuccess(int cr, int f, int success_to_add);

private:

    vector<vector<TripletPST>> table_of_triplets;


};


#endif //DE_RAM_JAPDE_CEC14_LSPR_TABLEFANDCR_H
