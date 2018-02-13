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
	Genome(const unsigned numStrings, const unsigned lenStrings);
	~Genome();
	void FitnessFactor();
	void Reproduction();
	void Roulette();
	void PrintGenome();
	unsigned GetFitnessSum();
private:
	struct Stats {
		std::vector< std::vector<bool> > genotype;
		std::vector< std::vector<unsigned> > locusPair;

		std::vector<unsigned> fitFactor;
		std::vector<unsigned> fitFactorRelative;
		std::vector<double> fitPercent;
		unsigned fitSum;
	};
	Stats Gen_New;
	Stats Gen_Old;
	std::vector<unsigned> BinToDec;
	


};

#endif