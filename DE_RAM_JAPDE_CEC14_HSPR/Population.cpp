//
// Created by Andres Ramos on 09/07/2020.
//

#include "Population.h"

using namespace std;


//constructor

Population::Population() {
    this->population_size = POPULATION_SIZE_INIT;

    for (int i = 0; i < this->population_size; i++) {
        this->individuals.insert(this->individuals.begin(), Individual());
    }

}

Population::Population(int size) {
    this->population_size = size;

    for (int i = 0; i < this->population_size; i++) {
        this->individuals.insert(this->individuals.begin(), Individual());
    }

}

vector<Individual> Population::getIndividuals() {
    return this->individuals;
}

void Population::setIndividuals(vector<Individual> to_set_population) {
    vector<Individual>::iterator it;
    it = to_set_population.begin();

    this->individuals.assign(it, to_set_population.end());

}

Individual Population::bestIndividual(void) {
    Individual best_individual = Individual();
    for (int i = 0; i < this->population_size; i++) {

        if (this->getIndividuals()[i].getFitness() < best_individual.getFitness()) {
            best_individual.setFitness(this->getIndividuals()[i].getFitness());
            best_individual.setComponents(this->getIndividuals()[i].getComponents());

        }
    }
    return best_individual;
}


//TODO to be checked set group? y que no se modifique la population
Individual Population::pBestIndividual(double p) {
    //Obtenemos los el numero de p mejores individuos en la poblacion actual
    int max_pbest_individuals = round((double) this->population_size * p);

    //si el valor es 0, ponemos el 4
    if (max_pbest_individuals < 1) { max_pbest_individuals = this->population_size; }

    //Escogemos un individo random entre ellos
    int random_pbest_individual_index = (rand() % max_pbest_individuals);


    Individual pbest_individual = Individual();

    vector<Individual> individuals_sorted = this->getIndividuals();
    sort(individuals_sorted.begin(), individuals_sorted.end());


    pbest_individual.setFitness(individuals_sorted[random_pbest_individual_index].getFitness());
    pbest_individual.setComponents(individuals_sorted[random_pbest_individual_index].getComponents());
    pbest_individual.setGroup(individuals_sorted[random_pbest_individual_index].getGroup());

    return pbest_individual;
}

Individual Population::getIndividual(int position) {
    return this->individuals[position];
}

//TODO Posible fallo por paso de referencia cheeckar
void Population::setIndividual(int position, Individual ind) {
    this->individuals[position] = ind;
}

void Population::recalculateFitness(void) {
    Individual individual;
    for (int individual_i = 0; individual_i < this->population_size; individual_i++) {
        individual = Individual();
        individual.setComponents(this->getIndividual(individual_i).getComponents());
        individual.setFitness(individual.calculate_fitness());

        this->setIndividual(individual_i, individual);
    }

}

double Population::calculateMeanErrorToOptimumPopulation(int number_of_function) {
    double accumulated = 0;
    for (int i = 0; i < this->population_size; i++) {
        accumulated += abs(this->getIndividuals()[i].getFitness() - 100 * number_of_function);
    }
    return accumulated;
}

void Population::assignFitness(vector<double> fitness_vector) {
    for (int i = 0; i < this->population_size; i++) {
        this->individuals[i].setFitness(fitness_vector[i]);
    }
}

int Population::getPopulationSize(void) {
    return this->population_size;
}

void Population::reducePopulationInHalf() {
    int offset_second_half = this->population_size / 2;
    vector<Individual> vector_to_assign;

    for (int i = 0; i < this->population_size / 2; i++) {
        if (this->individuals[i].getFitness() < this->individuals[i + offset_second_half].getFitness()) {
            vector_to_assign.insert(vector_to_assign.end(), this->individuals[i]);
        } else {
            vector_to_assign.insert(vector_to_assign.end(), this->individuals[i + offset_second_half]);
        }
    }
    this->individuals.assign(vector_to_assign.begin(), vector_to_assign.end());
    this->population_size = vector_to_assign.size();

}


void Population::assignGroupToIndividuals(int group_size) {
    int group;
    for (int ind = 0; ind < this->population_size; ind++) {
        group = ceil(ind / group_size);
        this->individuals[ind].setGroup(group);
    }

}

void Population::setGroupToInd(int position, int group_value) {
    this->individuals[position].setGroup(group_value);
}




