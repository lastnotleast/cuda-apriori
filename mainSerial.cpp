#include "util.h"

int main(int argc, char** argv) {
    
	int sequentialCounter[ATRIBUTES_C];
	
	#pragma region Convert threshold to integer 
	if(argc != 3) {
		printf("\nInput: %s minimum_support minimum_confidence\n", argv[0]);
		exit(EXIT_FAILURE); 
	}
	cout << "\nStarting...\n";
	float support = atof(argv[1]), confidence = atof(argv[2]);
	int sup = support * TRANSACTIONS_L, conf = confidence * TRANSACTIONS_L;
	#pragma endregion 

	countFrequencyAndGetCombinations(sequentialCounter, sup, 1);

    cout << "\nFinished.";
		
	return 0;
}
