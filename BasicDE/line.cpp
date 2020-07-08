//
// Created by Andres Ramos on 10/05/2020.
//

#include "line.h"
#include <iostream>
using namespace std;


// Member functions definitions including constructor
Line::Line( double len) {
    cout << "Object is being created, length = " << len << endl;
    length = len;
}
void Line::setLength( double len ) {
    length = len;
}
double Line::getLength( void ) {
    return length;
}

