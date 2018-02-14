#include "Genome.h"


Genome::Genome(const unsigned numStrings, const unsigned lenStrings, const double mutationProbability) {
	//Generate random values for multidimensional vector
	srand(time(0));
	for(unsigned i=0; i<numStrings; i++){
		std::vector<bool> m_row;			//Create an empty row
		for(unsigned j=0; j<lenStrings; j++){
			m_row.push_back(Random(2));		//Add element to column of row
		}
		Gen_New.genotype.push_back(m_row);		//Add row to the main vector
	}

	Gen_New.fitSum = 0;
	nGeneration = 0;
	totalMutation = 0;
	Gen_New.nMutation = 0;
	mutationProb = mutationProbability;

	std::vector<unsigned> m_row;
	for(unsigned i=0; i<numStrings; i++){
		m_row.push_back(0);
		m_row.push_back(0);
		m_row.push_back(0);
		Gen_Old.locusPair.push_back(m_row);
	}
};

Genome::~Genome() { Gen_New.genotype.clear(); };

//************************ Fitness Algorithms **************************
void Genome::FitnessFactor() {	//Based on x^2
	unsigned temp2, temp1 = 0;

	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		for(unsigned j=0; j<Gen_New.genotype[i].size(); j++){
			temp1 += Gen_New.genotype[i][j]*pow(2,Gen_New.genotype[i].size()-j-1);	//Convert binary to decimal
		}
		Gen_New.BinToDec.push_back(temp1);
		temp2 = pow(temp1,2); temp1 = 0;
		Gen_New.fitSum+=temp2;
		Gen_New.fitFactor.push_back(temp2);
		Gen_New.fitFactorRelative.push_back(Gen_New.fitSum);
	}
	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		Gen_New.fitPercent.push_back(static_cast<double>(Gen_New.fitFactor[i])/Gen_New.fitSum);
	}	
};

//************************ Selection Methonds **************************
void Genome::Selection(unsigned method) {		//Generate string pairs and locus point
	switch(method) {
		case 0: Roulette(); break;
		default: Roulette(); break;
	};
};


void Genome::Roulette() {
	unsigned locus,cond,m,n;
	std::vector<unsigned> m_row;			//Create an empty row
	std::vector<unsigned> n_row;			//Create an empty row


	for(unsigned i=0; i<Gen_New.genotype.size()/2; i++){
		m_row.clear(); n_row.clear();

		cond = Random(Gen_New.fitSum); m=0;
		for(unsigned k=0; Gen_New.fitFactorRelative[k]<cond; k++){m++;}

		cond = Random(Gen_New.fitSum); n=0;
		for(unsigned k=0; Gen_New.fitFactorRelative[k]<cond; k++){n++;}
		
		m_row.push_back(m);		//First Pair First Row
		n_row.push_back(n);		//First Pair Second Row
		m_row.push_back(n);		//Second Pair First Row
		n_row.push_back(m);		//Second Pair Second Row

		locus = Random(Gen_New.genotype[i].size());
		m_row.push_back(locus);
		n_row.push_back(locus);

		Gen_New.locusPair.push_back(m_row);
		Gen_New.locusPair.push_back(n_row);
	}
};

//************************ Crossover ***********************************
void Genome::Crossover() {
	Gen_Old = Gen_New;
	Gen_New = {};				//Empty structure
	Gen_New.nMutation = 0;

	std::vector<bool> m_row;	//Create placeholder empty row
	unsigned locus,pair1, pair2;

	//Splice each pair 
	for(unsigned i=0; i<Gen_Old.locusPair.size(); i++){
		pair1 = Gen_Old.locusPair[i][0];
		pair2 = Gen_Old.locusPair[i][1];
		locus = Gen_Old.locusPair[i][2];

		for(unsigned j=0; j<locus; j++){
			m_row.push_back(Gen_Old.genotype[pair1][j]);
		}
		for(; locus<Gen_Old.genotype[pair1].size(); locus++){
			m_row.push_back(Gen_Old.genotype[pair2][locus]);
		}
		Gen_New.genotype.push_back(m_row);
		m_row.clear();
		Mutations(i);	
	}

	totalMutation+=Gen_New.nMutation;
};

//************************ Mutations ***********************************
void Genome::Mutations(unsigned stringNum) {
	unsigned cond, range=0;

	if(mutationProb>0) {
		for(double i=mutationProb; i<100; i*=10) {range++;};
	}

	range = pow(10,range);

	for(unsigned i=0; i<Gen_New.genotype[stringNum].size(); i++){
		cond = Random(range);
		if(mutationProb*range/100 > cond) {
			if(Gen_New.genotype[stringNum][i] == 0){Gen_New.genotype[stringNum][i]=1;}
			else{Gen_New.genotype[stringNum][i]=0;}
			Gen_New.nMutation++;
		}
	}
};

//************************ Statistics **********************************
void Genome::Statistics() {
	//Fitness Factor Sum
	//for(unsigned i=0; i<Gen_New.fitFactor.size(); i++) {Gen_New.fitSum += Gen_New.fitFactor[i]; }

	//Highest Performance (STORE DATA) and Lowest Performance
	Gen_New.largestFF = 0;
	Gen_New.smallestFF = 0xFFFFF;
	for(unsigned i=0; i<Gen_New.fitFactor.size(); i++) {
		if(Gen_New.fitFactor[i]>Gen_New.largestFF) {Gen_New.largestFF=Gen_New.fitFactor[i]; }
		if(Gen_New.fitFactor[i]<Gen_New.smallestFF) {Gen_New.smallestFF=Gen_New.fitFactor[i]; }
	}

	nGeneration++;
};

//************************ Results *************************************
void Genome::PrintGenome() {
	Statistics();

	std::cout << "________________________________________________________________________________________" << std::endl;
	std::cout << "| Index |" << "  Value   |" << "  String          |" << " Parents |" << " Locus |" << " Fitness Factor |" << " Relative FF |" << std::endl;
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;

	for(unsigned i=0; i<Gen_New.genotype.size(); i++){
		std::cout << "|  " << std::left << std::setw(5) << i 
				<< "|  " << std::setw(8) << Gen_New.BinToDec[i] 
				<< "|  " << std::setw(16) << PrintString(i)
				<< "| (" << std::right << std::setw(2) << CompareParent(i,0)
				<< ","   << std::setw(2) << CompareParent(i,1) << ") "
				<< "|  " << std::left << std::setw(5) << Gen_Old.locusPair[i][2]
				<< "|  " << std::setw(14) << Gen_New.fitFactor[i]
				<< "|  " << std::setw(11) << std::setprecision(2) << Gen_New.fitPercent[i]*100
				<< "|  "
				<< std::endl;
	}

	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::left 
			<< "| Gen " << std:: setw(5) << nGeneration
			<< "| FF Sum: " << std::setw(10) << Gen_New.fitSum
			<< "| High FF: " << std::setw(8) << Gen_New.largestFF
			<< "| Lowe FF: " << std::setw(8) << Gen_New.smallestFF
			<< "| nMutations: " << std::setw(4) << Gen_New.nMutation
			<< "|"
			<< std::endl;
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
	std::cout << std::left 
			<< "| Total Mutations " << std:: setw(5) << totalMutation
			<< "|"
			<< std::endl;
	std::cout << "----------------------------------------------------------------------------------------" << std::endl;
};

std::string Genome::PrintString(unsigned i){
	std::string chromo;
	for(unsigned k=0; k<Gen_New.genotype[i].size(); k++){
		chromo += std::to_string(Gen_New.genotype[i][k]);
	}
	return chromo;
};

std::string Genome::FindPair(unsigned i){
	std::string pair;
	for(unsigned k=0; i<Gen_New.locusPair.size(); k++) {
		if(Gen_New.locusPair[k][0]==i){
			pair += std::to_string(Gen_New.locusPair[k][1]);
		}
		else pair = "-";
	}
	return pair;
};

std::string Genome::CompareParent(unsigned i, bool op){
	std::string sParent, lParent;
	unsigned cond = op;

	if(Gen_Old.locusPair[i][0]>Gen_Old.locusPair[i][1]){ 
		lParent += std::to_string(Gen_Old.locusPair[i][0]);
		sParent += std::to_string(Gen_Old.locusPair[i][1]);  
	}
	else{
		lParent += std::to_string(Gen_Old.locusPair[i][1]);
		sParent += std::to_string(Gen_Old.locusPair[i][0]);  
	}

	switch(cond){
		case 0:		return sParent;	//Find smallest
		case 1:	 	return lParent;  //Find largest
		default:	return "ERROR";
	};
}


//************************ Utilities ***********************************
unsigned Genome::Random(unsigned Range){return (rand()%Range); };

unsigned Genome::GetFF(){
	return Gen_New.fitSum;
};











// *********************** Example Main ********************************
int main() {
	//Create new gene
	unsigned population = 20;
	unsigned lenStrings = 8;
	double mutationProbability = 0.2; 	//As a percentage 0.2 is 0.2%
	Genome myGenome(population, lenStrings, mutationProbability);

	unsigned i=0;
	while(i<1300500){
		myGenome.FitnessFactor();
		myGenome.Selection(0);
		myGenome.PrintGenome();
		i=myGenome.GetFF();
		myGenome.Crossover();
		//i++;
	}

	return 0;
}

/*
 * Over time without mutations the strings average out, at this point we are no 
 * longer advancing the system by splicing but rather by random chance of mutation.
 */