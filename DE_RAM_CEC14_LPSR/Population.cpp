//
// Created by Andres Ramos on 09/07/2020.
//

#include "Population.h"
using namespace std;


//constructor

Population::Population() {
    this->population_size = POPULATION_SIZE_INIT;

    for (int i = 0 ; i < this->population_size; i++) {
       this->individuals.insert(this->individuals.begin(),Individual());
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



void Population::toString(void) {
    std::cout << "output from Population function";
    std::cout << "The population individuals are :  \n";

    for (int i = 0; i < this->population_size; i++) {
        cout << "Element number " << i << "\n";
        cout << this->individuals[i].toString();
    }

}

Individual Population::bestIndividual(void) {
    Individual best_individual = Individual();
    for (int i = 0; i < this->population_size; i++) {

        if (this->getIndividuals()[i].getFitness() < best_individual.getFitness()) {
            best_individual.setFitness(this->getIndividuals()[i].getFitness());
            best_individual.setComponents(this->getIndividuals()[i].getComponents()) ;

        }
    }
    return best_individual;
}

Individual Population::getIndividual(int position) {
    return this->individuals[position];
}

//TODO Posible fallo por paso de referencia cheeckar
void Population::setIndividual(int position, Individual ind) {
    this->individuals[position] = ind;
}

void Population::recalculateFitness(void){
    Individual individual;
    for (int individual_i = 0; individual_i< this->population_size; individual_i++) {
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
    for (int i = 0; i <this->population_size; i++) {
        this->individuals[i].setFitness(fitness_vector[i]);
    }
}
int Population::getPopulationSize(void) {
    return this->population_size;
}

int Population::WorstIndividualPosition(void) {
    int worst_ind_position = 0;
    for (int position = 0; position < this->population_size; position++) {
        if (this->getIndividual(position).getFitness() > this->getIndividual(worst_ind_position).getFitness()) {
            worst_ind_position = position;
        }
    }
    return worst_ind_position;
}

void Population::removeIndividual(int pos) {
    this->individuals.erase(this->individuals.begin() + pos);
}

void Population::reducePopulation(int number_of_ind_to_reduce) {
    for (int i = 0; i < number_of_ind_to_reduce; i++) {
        removeIndividual(WorstIndividualPosition());
    }
}








