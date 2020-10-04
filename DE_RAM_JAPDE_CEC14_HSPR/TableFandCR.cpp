//
// Created by Andres Ramos on 17/09/2020.
//

#include "TableFandCR.h"

TableFandCR::TableFandCR() {

    std::vector<std::vector<TripletPST>> fog(AMOUNT_OF_POSSIBLE_CR, std::vector<TripletPST>(AMOUNT_OF_POSSIBLE_F, TripletPST(AMOUNT_OF_POSSIBLE_CR * AMOUNT_OF_POSSIBLE_F)));
    table_of_triplets.assign(fog.begin(), fog.end());
}


vector<double> TableFandCR::getProbabilityFromRow(int row) {
    vector<double> vector_of_probabilities(AMOUNT_OF_POSSIBLE_F, -1);

    for (int i_f = 0; i_f < AMOUNT_OF_POSSIBLE_F; i_f++) {
        vector_of_probabilities[i_f] = table_of_triplets[row][i_f].getProbability();
    }
    return vector_of_probabilities;
}

vector<double> TableFandCR::getProbabilityFromCol(int col) {
    vector<double> vector_of_probabilities(AMOUNT_OF_POSSIBLE_CR, -1.0);

    for (int i_cr = 0; i_cr < AMOUNT_OF_POSSIBLE_CR; i_cr++) {
        vector_of_probabilities[i_cr] = table_of_triplets[i_cr][col].getProbability();
    }
    return vector_of_probabilities;
}

vector<double> TableFandCR::getProbabilityFromCols(void) {
    vector<double> vector_to_return(AMOUNT_OF_POSSIBLE_F, -1.0);
    for (int col_f = 0; col_f < AMOUNT_OF_POSSIBLE_F; col_f++) {
        vector_to_return[col_f] = getAccumulatedProbabilityFromCol(col_f);
    }
    return vector_to_return;
}

double TableFandCR::getAccumulatedProbabilityFromRow(int row) {
    double result = 0.0;

    for (int i_f = 0; i_f < AMOUNT_OF_POSSIBLE_F; i_f++) {
        result += table_of_triplets[row][i_f].getProbability();
    }
    return result;
}

double TableFandCR::getAccumulatedProbabilityFromCol(int col) {
    double result = 0.0;

    for (int i_cr = 0; i_cr < AMOUNT_OF_POSSIBLE_CR; i_cr++) {
        result += table_of_triplets[i_cr][col].getProbability();
    }
    return result;
}


void TableFandCR::addTries(int cr, int f, int tries_to_add) {
    int tries;
    tries = table_of_triplets[cr][f].getTries();
    table_of_triplets[cr][f].setTries(tries + tries_to_add);
}

void TableFandCR::addSuccess(int cr, int f, int success_to_add) {
    int success;
    success = table_of_triplets[cr][f].getSuccess();
    table_of_triplets[cr][f].setSuccess(success + success_to_add);
}


void TableFandCR::updateTable(double eva_maxeva_ratio) {
    cout << "updateTable_M table";
    double increment = 0.0;
    double probability_to_set_first;
    double probability_to_set_second;
    double probability_to_set;
    for (int rowCr = 0; rowCr < AMOUNT_OF_POSSIBLE_CR; rowCr++) {
        for (int colF = 0; colF < AMOUNT_OF_POSSIBLE_F; colF++) {
            increment = incrementMcrf(rowCr, colF, eva_maxeva_ratio);

            probability_to_set_first = (1 - EPA) * table_of_triplets[rowCr][colF].getProbability();
            probability_to_set_second = EPA * increment;
            probability_to_set = probability_to_set_first + probability_to_set_second;
            table_of_triplets[rowCr][colF].setProbability(probability_to_set);
        }
    }
}

double TableFandCR::incrementMcrf(int rowCr, int colF, double eva_maxeva_ratio) {

    double upper_part;
    double down_part = 0;
    double result;


    double Epf = EPf(colF, eva_maxeva_ratio);

    if (table_of_triplets[rowCr][colF].getTries() == 0) {
        upper_part = ((double) this->table_of_triplets[rowCr][colF].getSuccess() * Epf/ 1);
    } else {
        upper_part = ((double) this->table_of_triplets[rowCr][colF].getSuccess() * Epf/ (double) this->table_of_triplets[rowCr][colF].getTries());

    }


    for (int row = 0; row < AMOUNT_OF_POSSIBLE_CR; row++) {
        for (int col = 0; col < AMOUNT_OF_POSSIBLE_F; col++) {
            Epf = EPf(col, eva_maxeva_ratio);
            if (table_of_triplets[row][col].getTries() == 0) {
                down_part += ((double) this->table_of_triplets[row][col].getSuccess() * Epf / 1);
            } else {
                down_part += ((double) this->table_of_triplets[row][col].getSuccess() * Epf / (double) this->table_of_triplets[row][col].getTries());

            }
        }
    }

    result = upper_part / down_part;

    return result;

}

double TableFandCR::EPf(int val_f, double eva_maxeva_ratio) {
    double result;

    double division;
    double exponent_with_ratio;


    division = (double) val_f / 10.0;
    if (division == 0.0) division = 0.001;

    exponent_with_ratio = exp(-pow(eva_maxeva_ratio, 3));

    result = division * exponent_with_ratio;

    return result;
}

void TableFandCR::resetTripletsKeepProbabilities() {
    for (int cr = 0; cr < this->AMOUNT_OF_POSSIBLE_CR; cr++) {
        for (int f = 0; f < this->AMOUNT_OF_POSSIBLE_F; f++) {
            this->table_of_triplets[cr][f].resetTripletKeepProb();
        }
    }
}

