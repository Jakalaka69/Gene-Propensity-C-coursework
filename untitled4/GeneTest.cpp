//
// Created by jaywh on 18/01/2024.
//
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include "Gene.h"
#include <string>
#include <cstring>
#include "Gene.h"

using namespace std;

//main test harness
bool Gene::testGene(){


    bool stillWorking = true;

    if(!updateGene()){
        stillWorking = false;
    };

    if(!testOperatorOverload()){
        stillWorking = false;
    };

    if(!testGetStatements()){
        stillWorking = false;
    };


    if(stillWorking){
        return true;
    }
    else{
        return false;
    }
}

//Testing to see if you can update the properties of a gene correctly
bool Gene::updateGene(){
    Gene testSubject;
    testSubject.ID = "At1g01170";

    testSubject.sequence ="tggtcaagatttctgagaatgaagaatcaagtaaaaacaaaataggattaaggaaggataattgtttttgttattaagtttatataattcgaattatggaaatttatttatgattattttggcgggtcagtttgttgagacgtttaaatacagtcggataaggaaattgctcacgtcgtgatctaatttatttgtatttatttgactttacgtgtctagaaagctacatgtgatgtagtcatttacaatcaaaatcatttgctttaatccttgacttaattcattctgtatttcgggttttatgagtttagaaaaaccatataaaacaaaaacttatttaactcccctagacctattaataaatgaaactacgaatctctaatctttagtgtatttacagttttccaacgaaatcatatgttataacacgacacgacctcaatagtcaataataagtagaatcatgttttgaacatgtcaaatgcagcactgattcgaaagaataaagaaaaaaagagttttgaatcgtaattctgcaagaattaaagtgtagtgtttaatatatgtggcattcgccgagatcatcttataatagagtatgtgtcatacgccgaaaacaatgttggacacttggacctttccttactgataaataaataaattcatatcaactagcaaattagcatattacaggttttggttataacaattactcgagctagacgtatgatgaaattcagcaaactagtagatttgctattatatcttcccttgtgatgattgtagttttgtctcttaataaaactagtaattaacgtttcagaaaacaatgcccattttggtaatttcacagagatttatccaaagtttttaaagagataagacgatagagttggacgaccgtcttccaccGTTGAATTCTTCTGGAACTGGAGTCCACTGTTTAAGCTTCACTGTCTCTGAATCGGCAAAGGTAAACGTATCAATTATTCTACAAACCCTTTTATTTTTCTTTTGAATTACCGTCTTCATTGGTTATATGATAACTTGATAAGTAAAGCTTCAATAATTGAATTTGATCTGTGTTTTTTTGGCCTTAATACTAAATCCTTACATAAGCTTTGTTGCTTCTCCTCTTGTGAGTTGAGTGTTAAGTTGTAATAATGGTTCACTTTCAGCTTTAGAAGAAAATG";
    testSubject.setPropensity(1.34);
    if(testSubject.ID != "Default_Id" && testSubject.sequence != "Default_Seq" and testSubject.propensity != 0){
        cout << endl << "--Successfully updated the gene's data " << endl;
        return true;
    }
    else{
        cout << "--Error updating attributes";
        return false;
    }
}
//testing to see if the operator has been overloaded correctl
bool Gene::testOperatorOverload(){
    Gene geneBig;
    Gene geneSmall;
    geneBig.propensity = 12.0;
    geneSmall.propensity = -4.5;
    if(geneBig > geneSmall){
        cout << "--Comparison operator '>' working" << endl;
        return true;
    }
    else{
        cout << "--Comparison operator '>' not working" << endl;
        return false;
    }
}

//testing the get statements to see if they correctly retrieve data
bool Gene::testGetStatements(){
    Gene testSubject;
    testSubject.ID = "01754";
    testSubject.sequence = "gcgaacat";
    testSubject.propensity = 3.921;
    if(testSubject.getId() == "01754" && testSubject.getSequence() == "gcgaacat" && testSubject.getPropensity() == 3.921){
        cout << "--'Get' statements working accordingly" << endl;
        return true;
    }
    else{
        cout << "--'Get' statements not working" << endl;
        return false;
    }
}


