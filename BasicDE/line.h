//
// Created by Andres Ramos on 10/05/2020.
//

#ifndef BASICDE_LINE_H
#define BASICDE_LINE_H


class Line {
public:
    void setLength( double len );
    double getLength( void );
    Line(double len);  // This is the constructor

private:
    double length;
};


#endif //BASICDE_INDIVIDUAL_H
