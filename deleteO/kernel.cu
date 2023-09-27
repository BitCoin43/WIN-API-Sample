#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>

const int size = 1080 * 1920 * 1024;

__global__ void test(int* input, int* output, int width) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	int g = input[x] * 8231 + 3224;
	g /= 3;
	output[x] = g;
}

__global__ void set(int* input, int width) {
	int x = blockIdx.x * blockDim.x + threadIdx.x;
	for (int i = 0; i < 1920; i++) {
		input[x + i * 1080 * 1024] = x;
	}
	
}

uint64_t now() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

int main() {
	int* inp = nullptr;
	int* out = nullptr;

	uint64_t befor = now();

	cudaMalloc((void**)&inp, sizeof(int) * size);
	cudaMalloc((void**)&out, sizeof(int) * size);

	set<<<1080, 1024>>>(inp, size);


	
	cudaFree(inp);
	cudaFree(out);

	uint64_t after = now();
	std::cout << "For all: " << after - befor << "ms" << std::endl;

	return 0;
}