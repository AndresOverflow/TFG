//
// Created by Andres Ramos on 09/07/2020.
//

#include "Population.h"
using namespace std;


//constructor

Population::Population() {
    for (int i = 0 ; i < POPULATION_SIZE; i++) {
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

    for (int i = 0; i < POPULATION_SIZE; i++) {
        cout << "Element number " << i << "\n";
        cout << this->individuals[i].toString();
    }

}

Individual Population::bestIndividual(void) {
    Individual best_individual = Individual();
    for (int i = 0; i < POPULATION_SIZE; i++) {

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
    for (int individual_i = 0; individual_i< POPULATION_SIZE; individual_i++) {
        individual = Individual();
        individual.setComponents(this->getIndividual(individual_i).getComponents());
        individual.setFitness(individual.calculate_fitness());

        this->setIndividual(individual_i, individual);
    }

}

double Population::calculateMeanFitnessPopulation(int number_of_function) {
    double accumulated = 0;
    for (int i = 0; i < POPULATION_SIZE; i++) {
        accumulated += abs(this->getIndividuals()[i].getFitness() - 100 * number_of_function);
    }
    return accumulated;
}

void Population::assignFitness(vector<double> fitness_vector) {
    for (int i = 0; i <POPULATION_SIZE; i++) {
        this->individuals[i].setFitness(fitness_vector[i]);
    }

}





