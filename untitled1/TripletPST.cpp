//
// Created by Andres Ramos on 15/08/2020.
//

#include "TripletPST.h"


//constructor
TripletPST::TripletPST(int mutation_strategies) {
    this->probability = 1/ mutation_strategies;
    this->tries = 0;
    this->success = 0;

}

double TripletPST::getProbability(void){
    return this->probability;
}

void TripletPST::setProbability(double probability) {
    TripletPST::probability = probability;
}

int TripletPST::getTries(void){
    return this->tries;
}

void TripletPST::setTries(int tries) {
    TripletPST::tries = tries;
}

int TripletPST::getSuccess(){
    return this->success;
}

void TripletPST::setSuccess(int success) {
    TripletPST::success = success;
}
