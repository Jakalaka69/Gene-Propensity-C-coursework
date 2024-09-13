//
// Created by jaywh on 18/01/2024.
//

#ifndef INC_2024PROJECT_GENE_H
#define INC_2024PROJECT_GENE_H
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
using namespace std;
class Gene {
public:
    //declare attributes
    std::string ID;
    std::string sequence;
    double propensity;
    Gene();
    //declare methods and functions
    bool operator>(Gene &gene2 );
    void setPropensity(double d);
    friend istream& operator>>(istream& s, Gene& g);
    friend ostream& operator<<(ostream& s, Gene& g);
    std::string getId()const;
    std::string getSequence() const;
    double getPropensity() const;
    static bool testGene();
    static bool updateGene();
    static bool testOperatorOverload();
    static bool testGetStatements();
};


#endif //INC_2024PROJECT_GENE_H
