//
// Created by Andres Ramos on 15/08/2020.
//

#ifndef UNTITLED1_TRIPLETPST_H
#define UNTITLED1_TRIPLETPST_H

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

private:


    double probability;
    int tries;
    int success;
};


#endif //UNTITLED1_TRIPLETPST_H
