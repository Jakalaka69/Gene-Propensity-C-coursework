/******************************************************************************

File        : main.cpp

Date        : Wednesday 15th April 2022

Author      : Gavin Cawley

Description : Prototype implementation of a program to identify genes with
              the greatest propensity for glucose response, based on the
              presence of specific sequence features of the upstream promoter
              region [1].

              Note that this program is just a prototype system to be used to
              refine the project specifications.  There may be bugs and areas
              where the code is inefficient.  These issues will be addressed
              as the program is iteratively improved/refactored.

Notes       :

References  : [1] Li, Y., Lee, K.-K., Walsh, S., Smith, C., Hadingham, S.,
                  Sorefan, K., Cawley, G. and Bevan, M. W., "Establishing
                  glucose- and ABA-regulated transcription networks in
                  Arabidopsis by microarray analysis and promoter
                  classification using a Relevance Vector Machine", Genome
                  Research, vol. 16, pp 414-427, 2006.

History     : 15/04/2022 - v1.00 Initial prototype

******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <map>
#include "Gene.h"


using namespace std;

// declarations of functions defined later in this file

static double propensity(const string &sequence, map<string,double> *sites);

template <typename T, typename F> void bubbleSort(vector<T> &vec, F compare);

void displayGene(const Gene &gene);

int main()
{
    if(!Gene::testGene()){
        cout << "------------Test harness Failed------------";
    }
    else{
        cout << "------------Test harness Succeeded------------";
    }
   // load the database of Arabidopsis promoter sequences

   vector<Gene> genes;
   vector<Gene>* genesPtr = &genes;

   Gene gene;





    ifstream is("arabidopsis.csv", ifstream::in);




   while (is >> gene)
   {
       Gene* geneptr = &gene;
      genes.push_back(*geneptr);
   }



   // compute the glucose response propensity for each gene

   for (Gene &g : genes)
   {

      g.setPropensity(propensity(g.getSequence(), nullptr));
   }

   // sort genes in order of their propensity for glucose response

   bubbleSort(*genesPtr, [](Gene &a,Gene &b) {return a > b;});

   // display the protein with the highest propensity for glucose response

   displayGene(genes[0]);

   // save list of the top 20 up-regulated genes for subsequent analyses

   ofstream os("top20.csv");
    
   for (size_t i = 0; i < 20; i++)
   {

      os << genes[i] << endl;
   }

   os.close();

   return EXIT_SUCCESS;
}

/******************************************************************************

Function    : propensity

Parameters  : sequence - a const reference to a string containing the sequence
                         data for a promoter region

              map<string,double> *sites - optional pointer to a map used to
                                          store the contribution of each
                                          transcription factor binding site to
                                          the overall propensity

Returns     : double - value of propensity for glucose response

Description : Determine the propensity for glucose regulation based on an
              analysis of the upstream promoter region, using the motifs and
              scores identified by Li et al. [1].  If both arguments are
              provided, the second is used to store the contribution of each
              transcription factor binding site to the overall propensity
              score.

Notes       : The code is currently rather inefficient as it sequentially
              checks for each binding site motif in turn.  A finite state
              automata that recognised the entire language would likely be
              more efficient.

******************************************************************************/

double propensity(const string &seq, map<string,double> *sites)
{
   static const struct
   {
      string motif;

      double score;
   }
   bindingSites[] =
   {
      { "aaaccctaa", +2.9895 },
      { "ggwagggt",  +1.3346 },
      { "aacgtgt",   +1.1033 },
      { "acggg",     +0.9637 },
      { "gcggcaaa",  +0.9067 },
      { "gttaggtt",  +0.8397 },
      { "rccgac",    +0.8076 },
      { "gataagr",   -3.3202 },
      { "gataa",     -2.1431 },
      { "gataag",    -0.7107 },
      { "ggata",     -3.2140 },
      { "acgtggca",  -1.1698 },
      { "taacgta",   -0.9167 },
      { "aaaatatct", -0.8441 }
   };

   double propensity = 0.0;

   for (auto& site : bindingSites)
   {
      double score = 0.0;

      int idx = -1;

      while ((idx = seq.find(site.motif, idx+1)) != string::npos)
      {
         score += site.score;
      }

      propensity += score;

      if (sites != nullptr)
      {
         sites->insert({site.motif, score});
      }
   }

   return propensity;
}

/******************************************************************************

Function    : bubbleSort (template)

Parameters  : T       - template parameter given base type of vector
              F       - template parameter giving lambda/function pointer type
              vec     - reference to vector of base type T
              compare - lambda or function pointer used to define ordering

Returns     : void

Description : Basic implementation of bubble sort, implemented as a template
              so that it can be used with vectors of different types.  Bubble
              sort is not very efficient for large vectors, but is fine for
              prototyping with small datasets.  The compare function returns
              a true value if a pair of adjacent elements should be swapped
              and false otherwise.

******************************************************************************/

template <typename T, typename F> [[maybe_unused]] void bubbleSort(vector<T> &vec, F compare)
{
   bool sorted;

   do
   {

      sorted = true;
      for (int i = 1; i < vec.size(); i++)
      {

         if (compare(vec[i], vec[i-1]))
         {

            T temp   = vec[i];
            vec[i]   = vec[i-1];
            vec[i-1] = temp;

            sorted = false;
         }
      }
   }
   while (!sorted);

}

/******************************************************************************

Function    : displayGene

Parameters  : gene - const pointer to a Gene object

Returns     : void

Description : Display the information about a promoter, including an analysis
              of the contribution of each of the known transcription factor
              binding sites to the calculated propensity for glucose
              regulation.

******************************************************************************/

void displayGene(const Gene& gene)
{

   cout << endl
        << "Gene ID     = " << gene.getId()         << endl
        << "Propensity  = " << gene.getPropensity() << endl
        << "Sequence    = " << gene.getSequence()   << endl;

   // re-calculate propensity in order to analyse binding sites

   map<string,double> sites;

   propensity(gene.getSequence(), &sites);

   cout << endl
        << "Binding site contributions:"
        << endl
        << endl
        << setw(10)
        << "Motif"
        << "   Contribution"
        << endl;

   for (auto const& site : sites)
   {
      std::cout << setw(10)
                << site.first
                << "   "
                << showpos
                << site.second
                << std::endl;
   }
}

/*****************************************************************************/