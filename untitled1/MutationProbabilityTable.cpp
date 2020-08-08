//
// Created by Andres Ramos on 08/08/2020.
//

#include "MutationProbabilityTable.h"

MutationProbabilityTable::MutationProbabilityTable() {

}

int MutationProbabilityTable::updateTable() {
    return 0;
}

int MutationProbabilityTable::getNumberOfGroups() {
    return number_of_groups;
}

void MutationProbabilityTable::setNumberOfGroups(int number_of_groups) {
    this->number_of_groups = number_of_groups;
}

int MutationProbabilityTable::getNumberOfElementsPerGroup() {
    return number_of_elements_per_group;
}

void MutationProbabilityTable::setNumberOfElementsPerGroup(int number_of_elements_per_group) {
    this->number_of_elements_per_group = number_of_elements_per_group;

}

double MutationProbabilityTable::getProbability(int group, int element) {
    return table_of_probabilities[group][element];
}
/*
MutationProbabilityTable::setNumberOfGroups(int number_of_groups) {
    this->number_of_groups = number_of_groups;
}
*/