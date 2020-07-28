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

string Population::toString(void) {
    std::cout << "output from Population function";
    std::cout << "The population individuals are :  \n";

    for (int i = 0; i < this->individuals.size(); i++) {
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
