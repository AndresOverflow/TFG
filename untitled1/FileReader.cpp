//
// Created by Andres Ramos on 04/08/2020.
//

#include <fstream>
#include "FileReader.h"

using namespace std;


Population FileReader::setPopulationIndividualsFromFile() {
    Population population_to_fill_with_data = Population();

    fstream file_descriptor;
    string word;
    string prefix, sample_number, infix, dimension_number, sufix, file_name;
    prefix = "InputFiles/shuffle_data_";
    infix = "_D";
    dimension_number = to_string(Individual::DIMENSION);
    sufix = ".txt";
    vector<double> parameters;
    int value;


    for (int i = 0; i < Population::POPULATION_SIZE; i++) {
        sample_number = std::to_string(i + 1);
        file_name = prefix + sample_number + infix + dimension_number + sufix;
        cout << "Reading file with the name :" << file_name << "\n";

        file_descriptor.open(file_name.c_str());
        if (file_descriptor.is_open()){
            cout << "file found";
            while (file_descriptor >> word) {
            value = stoi(word);
            parameters.insert(parameters.end(),value);
            cout << value << endl;
            }
        } else {
            cout << "file not found";
        }

        population_to_fill_with_data.setIndividual(i, parameters);
        parameters = {};
        file_descriptor.close();
    }


    population_to_fill_with_data.toString();


    return population_to_fill_with_data;
}


