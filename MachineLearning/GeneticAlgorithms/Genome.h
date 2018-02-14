#ifndef GENOME_H
#define GENOME_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iomanip>

class Genome {
public:
	Genome(const unsigned numStrings, const unsigned lenStrings, const double mutationProbability);
	~Genome();
	void FitnessFactor();
	void Selection(unsigned method);
	void Crossover();
	void Statistics();
	void PrintGenome();
	unsigned GetFF();
private:
	void Roulette();
	void Mutations(unsigned stringNum);
	std::string PrintString(unsigned i);
	std::string FindPair(unsigned i);
	std::string CompareParent(unsigned i, bool op);
	unsigned Random(unsigned range);
	struct Stats {
		std::vector< std::vector<bool> > genotype;
		std::vector< std::vector<unsigned> > locusPair;

		std::vector<unsigned> BinToDec;
		std::vector<unsigned> fitFactor;
		std::vector<unsigned> fitFactorRelative;
		std::vector<double> fitPercent;
		unsigned fitSum;
		unsigned largestFF;
		unsigned smallestFF;
		unsigned nMutation;
	};
	Stats Gen_New;
	Stats Gen_Old;
	
	double mutationProb; //In percent
	unsigned totalMutation;
	unsigned nGeneration;


};

#endif