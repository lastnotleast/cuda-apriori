#include "util.h"

__global__ void cudaFrequencyCounter(int *input, int *counter);

void launchKernel(int *dev_report, int *dev_count) {
	int blocks = TRANSACTIONS_L;
	int threads = ATRIBUTES_C;
	cout << "\nBlocks = " << blocks << " | Threads per Blocks = " << threads << endl;
	cudaFrequencyCounter<<< blocks, threads >>>(dev_report, dev_count);
}

__global__ void cudaFrequencyCounter(int *input, int *counter) {
	int id = 0;
	int tx_col = threadIdx.x;
	int bx_lin = blockIdx.x;
	__shared__ int totalSum[ATRIBUTES_C];
	
	totalSum[tx_col] = 0; counter[tx_col] = 0;
	__syncthreads();
	
	if(tx_col < ATRIBUTES_C && bx_lin < TRANSACTIONS_L) {

		id = (ATRIBUTES_C * bx_lin) + tx_col; 

		if(input[id] == 1)
			atomicAdd(&totalSum[tx_col], 1);

		__syncthreads();
	}

	for(int i = 0; i < ATRIBUTES_C; i++)
		counter[i] = totalSum[i];
}

int main(int argc, char** argv) {
			
	int *dev_count, *dev_report;
	int parallelCounter[ATRIBUTES_C], sequentialCounter[ATRIBUTES_C];
	
	#pragma region Convert threshold to integer 
	if(argc != 3) {
		printf("\nInput: %s minimum_support minimum_confidence\n", argv[0]);
		exit(EXIT_FAILURE); 
	}
	cout << "\nStarting...\n";
	float support = atof(argv[1]), confidence = atof(argv[2]);
	int sup = support * TRANSACTIONS_L, conf = confidence * TRANSACTIONS_L;
	cout << "\nMAIN THRESHOLD " << sup << " " << conf << endl;	
	#pragma endregion 

	#pragma region Allocate memory 
	HANDLE_ERROR(cudaMalloc((void**)&dev_count, sizeof(parallelCounter)));
	HANDLE_ERROR(cudaMalloc((void**)&dev_report, sizeof(report)));
	HANDLE_ERROR(cudaMemcpy(dev_report, report, sizeof(report), cudaMemcpyHostToDevice));
	#pragma endregion 

	launchKernel(dev_report, dev_count);

	#pragma region Handle Memory 
	HANDLE_ERROR(cudaMemcpy(parallelCounter, dev_count, sizeof(parallelCounter), cudaMemcpyDeviceToHost));
	cudaFree(dev_report);
	cudaFree(dev_count);
	#pragma endregion

	cout << "\n\nFinished.\n\n";
	return 0;
}
