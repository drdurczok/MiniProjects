#include "Genome.h"


Genome::Genome(const unsigned numStrings, const unsigned lenStrings) {
	//Generate random values for multidimensional vector
	srand(time(0));
	for(unsigned i=0; i<numStrings; i++){
		std::vector<bool> m_row;			//Create an empty row
		for(unsigned j=0; j<lenStrings; j++){
			m_row.push_back(rand()%2);		//Add element to column of row
		}
		Gen_New.genotype.push_back(m_row);		//Add row to the main vector
	}

	Gen_New.fitSum = 0;
};

Genome::~Genome() { Gen_New.genotype.clear(); };

void Genome::FitnessFactor() {	//Based on x^2
	unsigned temp2, temp1 = 0;

	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		for(unsigned j=0; j<Gen_New.genotype[i].size(); j++){
			temp1 += Gen_New.genotype[i][j]*pow(2,Gen_New.genotype[i].size()-j-1);	//Convert binary to decimal
		}
		BinToDec.push_back(temp1);
		temp2 = pow(temp1,2); temp1 = 0;
		Gen_New.fitSum += temp2;
		Gen_New.fitFactor.push_back(temp2);
		Gen_New.fitFactorRelative.push_back(Gen_New.fitSum);
	}
	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		Gen_New.fitPercent.push_back(static_cast<double>(Gen_New.fitFactor[i])/Gen_New.fitSum);
	}	
};

void Genome::Reproduction() {
	unsigned temp,n;
	bool cond;
	std::vector<unsigned> m_row;			//Create an empty row

	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		do{
			m_row.clear();
			m_row.push_back(i);		//First Pair

			temp = rand()%Gen_New.fitSum; n=0;
			for(unsigned k=0; Gen_New.fitFactorRelative[k]<temp; k++){n++;}
			m_row.push_back(n);		//Second Pair

			cond = 0;
			for(unsigned j=0; j<Gen_New.locusPair.size(); j++){
				if((m_row[0]==Gen_New.locusPair[j][0] && m_row[1]==Gen_New.locusPair[j][1]) 
					|| (m_row[0]==Gen_New.locusPair[j][1] && m_row[1]==Gen_New.locusPair[j][0]) 
					|| (m_row[0]==m_row[1])) {cond = 1;}
			}

		} while(cond==1);
		m_row.push_back(rand()%Gen_New.genotype[i].size());		//Locus
		Gen_New.locusPair.push_back(m_row);
	}
};


void Genome::Roulette() {
	Gen_Old = Gen_New;
	Gen_New = {};

	std::vector<bool> m_row;			//Create an empty row
	unsigned locus,pair;

	//Splice each pair 
	for(unsigned i=0; i<Gen_Old.locusPair.size(); i++){
		locus = Gen_Old.locusPair[i][3];
		pair = Gen_Old.locusPair[i][2];

		for(unsigned j=0; j<locus; j++){
			if(rand()%1000==1){m_row.push_back(1);}
			else{m_row.push_back(Gen_Old.genotype[i][j]);}
		}
		for(; locus<Gen_Old.genotype[0].size(); locus++){
			if(rand()%1000==1){m_row.push_back(1);}
			else{m_row.push_back(Gen_Old.genotype[pair][locus]);}
		}
		Gen_New.genotype.push_back(m_row);
		m_row.clear();	
	}
	BinToDec.clear();
};

void Genome::PrintGenome() {
	std::cout << "Genotype Size: " << Gen_New.genotype.size() << std::endl;

	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		std::cout << std::setw(2) << i << std::setw(2) << "|" << std::left << std::setw(4) << BinToDec[i] << std::flush;
		for(unsigned j=0; j<Gen_New.genotype[i].size(); j++){
			std::cout << Gen_New.genotype[i][j] << std::flush;
		}
		std::cout << "\t" << std::left << "Pair: " << std::setw(6) << Gen_New.locusPair[i][1] << "Locus: " << Gen_New.locusPair[i][2] << "\t|FF:" << std::setw(8) << Gen_New.fitFactor[i] << std::fixed << std::setprecision(2) << std::setw(5) << Gen_New.fitPercent[i]*100 << std::setw(2) << "%" << "|" << std::endl;
	}

	std::cout << std::endl << "Fitness Sum: " << Gen_New.fitSum << std::endl << std::endl;
};

unsigned Genome::GetFitnessSum(){
	return Gen_Old.fitSum;
}




// ******************** Example Main **********************
int main() {
	//Create new gene
	unsigned numStrings = 20;
	unsigned lenStrings = 8;
	Genome myGenome(numStrings, lenStrings);

	unsigned i=0, sum=0;
	while(sum<1300400){
		myGenome.FitnessFactor();
		myGenome.Reproduction();
		if(i%200==0){myGenome.PrintGenome();}
		myGenome.Roulette();
		sum=myGenome.GetFitnessSum();
		i++;
	}
	myGenome.FitnessFactor();
	myGenome.Reproduction();
	myGenome.PrintGenome();
	std::cout << "It took " << i << " generations to train this program" << std::endl;

	return 0;
}