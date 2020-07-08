#include <iostream>
#include <string>
#include <vector>
#include "Individual.h"

using namespace std;

int population_size = 2;


vector<Individual> current_population {Individual(50),Individual(30)};
vector<Individual> offspring{Individual(100),Individual(70)};
double F = 1.25; //mutation factor
double CR = 1; //Crossover factor


void selection(){
    cout << "selection function";
    for (int i= 0; i< population_size; i++) {
        current_population[i].setComponents(offspring[i].getComponents());
        current_population[i].setFitness(offspring[i].getFitness());
    }
}


void crossover() {
    cout << "\n crossover \n";
}


void mutation() {
    cout << "\n crossover \n";
}




void DE_rand_1 (){

    srand((unsigned) time(0));

    int N_X_r1, N_X_r2, N_X_r3;
    Individual result;
    N_X_r1 = (rand() % population_size);
    N_X_r2 = (rand() % population_size);
    N_X_r3 = (rand() % population_size);

    result = current_population[N_X_r1] + (F * (current_population[N_X_r2] - current_population[N_X_r3]));


    cout << N_X_r1;


}

void minus(vector<double> resutlt, vector<double>){

}





int main() {



    cout <<"Let's execute the first DE ever";

    for (int i = 0; i < population_size; i++) {
        cout << current_population[i].toString();
    }

    for (int i = 0; i < population_size; i++) {
        cout << offspring[i].toString();
    }

    selection();

    cout << " \n After Selection \n";

    for (int i = 0; i < population_size; i++) {
        cout << current_population[i].toString();
    }

    cout << to_string(current_population[1].calculate_fitness());


    DE_rand_1();
    cout << "end of the program";

    return 0;

}
