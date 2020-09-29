//
// Created by Andres Ramos on 15/08/2020.
//

#ifndef DE_RAM_JAPDE_CEC14_LSPR_TRIPLETPST_H
#define DE_RAM_JAPDE_CEC14_LSPR_TRIPLETPST_H

#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <math.h>
#include <iostream>


using namespace std;

class TripletPST {

public:

    TripletPST(int mutation_strategies);

    double getProbability(void);

    void setProbability(double probability);

    int getTries(void);

    void setTries(int tries);

    int getSuccess(void);

    void setSuccess(int success);

    void resetTripletKeepProb();

private:


    double probability;
    int tries;
    int success;
};


#endif //DE_RAM_JAPDE_CEC14_LSPR_TRIPLETPST_H
