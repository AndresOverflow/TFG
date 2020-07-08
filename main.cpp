#include <iostream>
#include <vector>

using namespace std;


// global variables


int add(double x, double y) {
    return x+y;
}

double sumofarray(double vector[], int size_vector, std::vector<int> &vect2) {
    int vector_len =sizeof(vector)/sizeof(vector[0]);
    double result = 0;
    for (unsigned i = 0; i < size_vector; i++) {
        result = result + vector[i];

    }
    int len = vect2.size();
    return result;
}

// function declaration:
double getAverage(int arr[], int size) {
    int i, sum = 0;
    double avg;

    for (i = 0; i < size; ++i) {
        sum += arr[i];
    }
    avg = double(sum) / size;

    return avg;
}


int main2() {
    cout << "Pinche taera, yo quiero no quiero hacer TFG quiero comer fabada con Sandra!!!";


    // an int array with 5 elements.
    int balance[5] = {1000, 2, 3, 17, 50};
    double avg;

    // pass pointer to the array as an argument.
    avg = getAverage( balance, 5 ) ;

    //Local variables


    int no_initialized_variable;
    int x = 5;
    int y = 6;

    double values [] = {1, 2, 3, 4};
    double values2 [] = {1,2,3}; // array de 3
    double values3 [5] = {}; // de 0
    double values4 [9]; // basura
    double values5[5] = {}; // de 0

    int vector_len_out =sizeof(values)/sizeof(values[0]);
    vector<int> vect2;
    vect2.push_back(20);
    vect2.push_back(40);


    double sum_of_values = sumofarray(values, vector_len_out, vect2);



    int z = add(x,y);
    //int result = add(x,y);

    cout << "\n Initialized value";
    cout << no_initialized_variable;
    cout << "\n";
    cout << x;
    cout << y;
    cout << (x+y);
    return 0;
}

double average(std::vector<int> &vect){

    int result = 0;

    for (int i = 0; i< vect.size();i++) {
        result = result + vect.at(i);
    }


    return result/vect.size();
}

vector<int> copy_vector(std::vector<int> &vect2) {
    vector<int> vector2 = {10,20,30,40,50};
    std::vector<int>::iterator it;
    it = vect2.begin();
    vector2.assign(it,vect2.end());

    //vector2 = vect2;

    return vector2;
}

int main(void) {

    /*
    vector<int> vector_1 = {1,2,3,4,5};
    vector<int> vector_2 = {100,200,300,400,500};


    double avera = average(vector_1);

    vector_2 = copy_vector(vector_1);

    cout << &vector_2;

*/
    vector<int> vect = {1,2,3,4,5};
    vector<int> vect2 = {2,3,5,7,8};
    vector<int>::iterator it;
    it = vect2.begin();
    vect.assign(it,vect2.end());
    vect = vect2;
    vect2[2] = 100;

    for (int i=0; i<vect.size(); i++)
        cout << vect[i] << " ";
}


