#include "util.h"

void getFrequentsAndCombine(int *frequencies, int minSup, int attempt) {
	vector<int> frequentItens;

	// Get the frequent itens
	for (int i = 0; i < ATRIBUTES_C; i++)
		if (frequencies[i] >= minSup)
			frequentItens.push_back(i);
	
	if (frequentItens.empty()) {
		cout << "\nNo more association rules\n";
		exit(EXIT_SUCCESS);
	}

	// Combine Frequent Itens
	vector<string> newCombination;
	string tempNewString = "";
	int itensLenght = frequentItens.size();
	int k = 1;
	for (int i = 0; i < itensLenght; i++)
		for (int j = i+1; j < itensLenght; j++)
			if (i != (itensLenght - 1)) {
				tempNewString = frequentItens[i] + "," + frequentItens[j];
				newCombination.push_back(tempNewString);
			}

	if (newCombination.empty()) {
		exit(EXIT_SUCESS);
	}

	// Convert string
	int convertedValue;
	string combinationString = "";
	vector<int> convertedCombination;
	for (int i = 0; i < newCombination.size(); i++) {
		combinationString = newCombination[i];
		for (int j = 0; j < combinationString.size(); j++) {
			if (strcmp(newCombination[i], ',') != 0) {
				convertedValue = atoi(newCombination[i]);
				convertedCombination.push_back(convertedValue);
			}
		}
	}
}

void countFrequencyAndGetCombinations(int *sum, int minSup, int attempt) {
	
	int i, j;

	cleanCounter(sum);
	
	// Count Frequency
	for (i = 0; i < TRANSACTIONS_L; i++)
		for (j = 0; j < ATRIBUTES_C; j++)
			if (report[i][j] == 1)
				sum[j] += 1;

	getFrequentsAndCombine(sum, minSup, attempt);
}
