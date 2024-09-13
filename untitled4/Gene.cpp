//
// Created by jaywh on 18/01/2024.
//
#include <iostream>
#include <iomanip>

#include "Gene.h"
#include <string>

using namespace std;

//Gene constructor
Gene::Gene(){
    ID = "Default_Id";
    sequence = "Default_Seq";
    propensity = 0;
}



// > overload function
bool Gene::operator>(Gene &gene2 ) {

    if(this->propensity > gene2.propensity){

        return true;
    }
    else{
        return false;
    }
}
//Get functions
string Gene::getId() const{
    return this->ID;
};
std::string Gene::getSequence() const{
    return this->sequence;
};
double Gene::getPropensity() const{
    return this->propensity;
}

void Gene::setPropensity(double d){
    this->propensity = d;
}
// >> overload function
istream& operator>>(istream& is, Gene &g){
    char comma;

    is >> quoted(g.ID) >> comma >> quoted(g.sequence) >> comma >> g.propensity;


    return is;
}

// << overload function
ostream& operator<<(ostream& os, Gene &g){

    os << quoted(g.ID) << "," << quoted(g.sequence) << "," << g.propensity;
    return os;
}