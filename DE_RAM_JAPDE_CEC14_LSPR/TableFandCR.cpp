//
// Created by Andres Ramos on 17/09/2020.
//

#include "TableFandCR.h"

TableFandCR::TableFandCR() {

    std::vector<std::vector<TripletPST>> fog(AMOUNT_OF_POSSIBLE_F, std::vector<TripletPST>(AMOUNT_OF_POSSIBLE_CR, TripletPST(AMOUNT_OF_POSSIBLE_F)));
    table_of_triplets.assign(fog.begin(),fog.end());
}

void TableFandCR::updateTable(double eva_maxeva_ratio) {
    cout << "updateTable_M table";
    double increment = 0.0
    double probability_to_set_first;
    double probability_to_set_second;
    double probability_to_set;
    for(int rowCr; rowCr < AMOUNT_OF_POSSIBLE_CR; rowCR++) {
        for (int colF = 0; colF < AMOUNT_OF_POSSIBLE_F; colF++) {
            increment = incrementMcrf(rowf, colcr, eva_maxeva_ratio);

            probability_to_set_first = (1 - EPA) * table_of_triplets[rowCr][colF].getProbability();
            probability_to_set_second = EPA * incrementMcrf(rowCr, colF, eva_maxeva_ratio);
            probability_to_set = probability_to_set_first + probability_to_set_second;
            table_of_triplets[rowCr][colF].setProbability(probability_to_set);
        }
    }
}

double TableFandCR::incrementMcrf(int rowCr, int colF, double eva_maxeva_ratio) {

    double upper_part;
    double down_part = 0.0;
    double result;

    double Epf = EPf(colF, eva_maxeva_ratio);

    upper_part = ((double)this->table_of_triplets[rowCr][colF].getSuccess() * Epf / (double)this->table_of_triplets[rowCr][colF].getTries());

    for(int row = 0; row < AMOUNT_OF_POSSIBLE_CR; row++) {
        for(int col = 0; col < AMOUNT_OF_POSSIBLE_F; col++) {
            down_part += ((double)this->table_of_triplets[row][col].getSuccess() * Epf / (double)this->table_of_triplets[row][col].getTries());
        }
    }

    result = upper_part / down_part;

    return result;

}

double TableFandCR::EPf(int val_f, double eva_maxeva_ratio) {
    result = 0;

    double division;
    double exponent_with_ratio;


    division = (double)val_f / 10.0;
    if (dision == 0.0) division = 0.001;

    exponent_with_ratio = exp(-pow(eva_maxeva_ratio, 3));

    result = division * exponent_with_ratio;

    return result;
}



