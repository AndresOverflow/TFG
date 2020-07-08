//
// Created by Andres Ramos on 10/05/2020.
//

#include <iostream>
#include "line.h"
#include "individual.h"


int main(){
    std::cout << "hello_world \n";

    int array [10] = {1,2,3,4,5,6,7,8,9,10};

    std::cout << array[2] << "\n";

    Line line(50);
    std::cout << line.getLength();


    Individual individual(5);
    std::string string = individual.tString();
    cout << string;








    return 0;


}

