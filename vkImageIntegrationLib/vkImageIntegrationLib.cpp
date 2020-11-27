#include <iostream>
#include <vector>
#include <chrono>
#include <vulkan/vulkan.hpp>
#include <kompute/Kompute.hpp>
#include "vkImageIntegrationLib.h"
namespace vkII {

	using namespace std;
	vkImageIntegration::vkImageIntegration()
	{
		
	}

	vkImageIntegration::~vkImageIntegration()
	{
		
	}

	void vkImageIntegration::do_comp()
	{

		kp::Manager mgr;
		const int n = 10000;
		const int m = 10000;

		vector<float> dataA(m*n);
		vector<float> dataB(m*n);

		vector<float> out_mat_gpu(m*n);
		vector<float> out_mat_cpu(m*n);
		
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				dataA[i*m + j] = 5.5+j;
				dataB[i*m + j] = 2-i;
			}
		}
		

		// 2. Explicitly create Kompute Tensors without initializing in GPU
		auto tensorInA = std::make_shared<kp::Tensor>(kp::Tensor(dataA));
		auto tensorInB = std::make_shared<kp::Tensor>(kp::Tensor(dataB));
		auto tensorOut = std::make_shared<kp::Tensor>(kp::Tensor(out_mat_gpu));
		
		// 3. Initialise the Kompute Tensor in GPU memory and map data into GPU
		mgr.evalOpAsyncDefault<kp::OpTensorCreate>({ tensorInA, tensorInB, tensorOut });
		
		static std::string shaderData = "C:/Users/alist/OneDrive/Development/vkImageIntegration/vkImageIntegrationLib/shaders/add.glsl";
		auto start_gpu = std::chrono::high_resolution_clock::now();
		kp::OpAlgoBase algo;
		// 4. Run operation with custom compute shader code asynchronously with explicit dispatch layout
		mgr.evalOpDefault<kp::OpAlgoBase>({ tensorInA, tensorInB,  tensorOut }, shaderData); // "shaderData" defined is below and can be glsl/spirv string, or path to file

		mgr.evalOpAwaitDefault();
		auto stop_gpu_compute = std::chrono::high_resolution_clock::now();
		mgr.evalOpDefault<kp::OpTensorSyncLocal>({ tensorOut });
		auto stop_gpu_transfer = std::chrono::high_resolution_clock::now();

		auto start_cpu = std::chrono::high_resolution_clock::now();

		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				out_mat_cpu[i*m + j] = dataA[i*m + j] + dataB[i*m + j];
			}
		}
		
		auto stop_cpu = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> gpu_elapsed_c = stop_gpu_compute - start_gpu;
		std::chrono::duration<double> gpu_elapsed_t = stop_gpu_transfer - stop_gpu_compute;
		std::chrono::duration<double> cpu_elapsed = stop_cpu - start_cpu;
		
		std::cout << "GPU Time compute: " << gpu_elapsed_c.count() << std::endl;

		std::cout << "GPU Time transfer: " << gpu_elapsed_t.count() << std::endl;
		std::cout << "CPU Time: " << cpu_elapsed.count() << std::endl;
		
		// Prints the output which is Output: { 2, 4, 6 }
		std::cout << "Out data: " <<  tensorOut->data()[4] <<" " << tensorOut->data()[5] << " " << tensorOut->data()[6]  << std::endl;
		std::cout << "Out data CPU: " << out_mat_cpu[4] << " " << out_mat_cpu[5] << " " << out_mat_cpu[6] << std::endl;

	}
}