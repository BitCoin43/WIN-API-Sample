
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>
#include <iostream>

__device__ int f(int n) {
    if (n == 0) return 5;
    if (n > 0 && n % 2 == 0) return 1 + f(n / 2);
    return f(n / 2);
}

__global__ void g(int *c)
{
    int i = blockIdx.x;
    int y = f(i);
    
    if (y == 7)
        *c = *c + 1;
  
}

int main()
{
    int* c = nullptr;
    int h = 0;

    cudaMalloc((void**)&c, sizeof(int));
    g << <1000000000, 1 >> > (c);
    
    cudaMemcpy(&h, c, sizeof(int), cudaMemcpyDeviceToHost);

    std::cout << h;
    return 0;
}

