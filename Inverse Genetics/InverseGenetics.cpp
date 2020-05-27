/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "simpio.h"
#include "set.h"
#include "map.h"
//#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);
Set<string> rnaSet(string protein, Map<char, Set<string> >& codons);
/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();


int main() {
    Map<char, Set<string> > codons = loadCodonMap();
	string protein = getLine("Enter protein: ");
	listAllRNAStrandsFor(protein, codons);
	
	return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }
	
    return result;
}

// wrapper method for rnaSet.
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons){
	cout << rnaSet(protein, codons) << endl;
}

/* this method returns set of strings with which protein can be assembled. 
	base case is when protein's length is 1, and recursive step is taking set from first protein,
	and adding set of the rest.
	
*/
Set<string> rnaSet(string protein, Map<char, Set<string> >& codons){
	Set<string> first = codons[protein[0]];
	if (protein.length() == 1){
		return first;
	}
	Set<string> result;
	Set<string> remaining = rnaSet(protein.substr(1), codons);
	foreach (string s1 in first){
		foreach(string s2 in remaining){
			result += s1 + s2;
		}
	}
	return result;
}