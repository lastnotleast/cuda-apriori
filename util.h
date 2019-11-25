#ifndef _UTIL_H_
#define _UTIL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <cuda.h>
#include <cuda_runtime.h>
#include "apriori.h"

using namespace std;

	#define TRANSACTIONS_L 5000
	#define ATRIBUTES_C 50
		
	extern int report[TRANSACTIONS_L][ATRIBUTES_C];

	static void HandleError(cudaError_t err, const char *file, int line) {
		if (err != cudaSuccess) {
				printf("%s in %s at line %d\n", cudaGetErrorString(err), file, line);
				exit(EXIT_FAILURE);
		}
	}
	#define HANDLE_ERROR( err ) (HandleError( err, __FILE__, __LINE__ ))

	void cleanCounter(int *counter) {
		for (int i = 0; i < ATRIBUTES_C; i++)
			counter[i] = 0;
	}
#endif
