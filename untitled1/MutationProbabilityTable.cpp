//
// Created by Andres Ramos on 08/08/2020.
//

#include "MutationProbabilityTable.h"

MutationProbabilityTable::MutationProbabilityTable(int group_size, double evaporation) {
    for(int group = 0; group < this->table_of_probabilities.size(); group++){
        for(int mutation_strategy = 0; mutation_strategy < this->table_of_probabilities[mutation_strategy].size(); mutation_strategy++){
            table_of_probabilities[group][mutation_strategy] = TripletPST();
        }
    }
    number_of_mutation_strategies = MUTATION_STRATEGIES;
    number_of_groups = Population::POPULATION_SIZE/group_size;
    this->evaporation_rate = evaporation;
}

//TODO finish function
void MutationProbabilityTable::updateTable() {
    cout << "updateTable";
    double probability_to_set_first;
    double probability_to_set_second;
    double probability_to_set;
    for(int group = 0; group<this->table_of_probabilities.size(); group++) {
        for (int mutation_strategy = 0; mutation_strategy < this->table_of_probabilities[mutation_strategy].size(); mutation_strategy++) {
            probability_to_set_first = (1 - evaporation_rate) * table_of_probabilities[group][mutation_strategy].getProbability();
            probability_to_set_second = evaporation_rate * (table_of_probabilities[group][mutation_strategy].getSuccess()/table_of_probabilities[group][mutation_strategy].getTries());
            probability_to_set = probability_to_set_first + probability_to_set_second;
            table_of_probabilities[group][mutation_strategy].setProbability(probability_to_set);
        }
    }
}

int MutationProbabilityTable::getNumberOfGroups(void) {
    return number_of_groups;
}

void MutationProbabilityTable::setNumberOfGroups(int number_of_groups) {
    this->number_of_groups = number_of_groups;
}

int MutationProbabilityTable::getNumberOfElementsPerGroup(void) {
    return number_of_mutation_strategies;
}

void MutationProbabilityTable::setNumberOfElementsPerGroup(int number_of_elements_per_group) {
    this->number_of_mutation_strategies = number_of_elements_per_group;
}

double MutationProbabilityTable::getProbability(int group, int mutation_strategy) {
    return table_of_probabilities[group][mutation_strategy].getProbability();
}

void MutationProbabilityTable::addTries(int group, int mutation_str, int tries_to_add) {
    int tries;
    tries = table_of_probabilities[group][mutation_str].getTries();
    table_of_probabilities[group][mutation_str].setSuccess(tries + tries_to_add);
}

void MutationProbabilityTable::addSuccess(int group, int mutation_str, int success_to_add) {
    int success;
    success = table_of_probabilities[group][mutation_str].getSuccess();
    table_of_probabilities[group][mutation_str].setSuccess(success + success_to_add);
}
