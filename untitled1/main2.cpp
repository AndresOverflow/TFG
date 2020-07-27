//
// Created by Andres Ramos on 09/07/2020.
//
#include <iostream>
#include <string>
#include <vector>
#include "Individual.h"



using namespace std;

int main2() {

    cout << "first trials";
    cout << "................................................";
    cout << "\n";
    cout << "how to initialize an array of vectors";
    cout << "\n";

    string string1 = "Sandra";
    string string2 = "Garcia";
    string string3 = string1 + " " + string2;
    cout << string3 + "\n";


    vector<int> vect1;
    vector<int> vect2;


    vect1 = {1,2,3,4,5};

    std::reverse(vect1.begin(),vect1.end());

    for (int x : vect1)
        cout << x << " ";

    cout << "Pointers over an array on c++";

    int Array[10];

    int *pLocation6 = &Array[6];
    int *pLocation0 = &Array[0];

    cout << "\n Position of the pointer pLocation6 : ";
    cout << (int) (size_t) pLocation6;
    cout << (int) (size_t) pLocation0;

    int *pLocation5 = reinterpret_cast<int *>(Array[5]);
    cout << "\n";
    cout << (int) (size_t) pLocation5;







    cout << "................................................";
    cout << "\n";
}