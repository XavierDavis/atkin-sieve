#define CL_TARGET_OPENCL_VERSION 120

#include <CL/cl.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

int main(){

	//----------------------------------------------------------------------INICJALIZACJA OPENCLA
	//Pobranie platform
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);
	std::cout << "Liczba platform: " << platforms.size() << std::endl;

	//Pobranie urządzeń
	cl::Platform platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
	std::cout << "Liczba urządzeń: " << devices.size() << std::endl;
	cl::Device device = devices.front();

	//Plik źródłowy
	std::ifstream inputFile("equations.cl");
	std::string src(std::istreambuf_iterator<char>(inputFile), (std::istreambuf_iterator<char>()));
	cl::Program::Sources sources(1, std::make_pair(src.c_str(), src.length() + 1));
	//Utworzenie kontekstu
	cl::Context context(device);
	//Utworzenie programu
	cl::Program program(context,sources);
	program.build("-cl-std=CL1.2");
	//Utworzenie kolejki
	cl::CommandQueue queue(context, device);

	std::string num;
	device.getInfo(CL_DEVICE_VERSION, &num);
	std::cout << "Wersja opencla: " << num << std::endl;
	//----------------------------------------------------------------------INICJALIZACJA OPENCLA

	long range = 0;
	std::cin >> range;
	if(range < 6)
		exit(1);

	// Krok 1. Utworzenie listy wyników
	std::vector<long> primes = {2, 3, 5};
	// Krok 2. Utworzenie listy reprezentującej sito + bufora OpenCLowego
	cl::Buffer sieveBuf(context, CL_MEM_READ_WRITE|CL_MEM_HOST_READ_ONLY, sizeof(int) * range);

	//Utworzenie 
	std::vector<int> r1 = {1, 13, 17, 29, 37, 41, 49, 53};
	cl::Buffer r1Buf(context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, r1.size() * sizeof(int), r1.data());
	
	std::vector<int> r2 = {7, 19, 31, 43};
	cl::Buffer r2Buf(context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, r2.size() * sizeof(int), r2.data());
	
	std::vector<int> r3 = {11, 23, 47, 59};
	cl::Buffer r3Buf(context, CL_MEM_READ_ONLY|CL_MEM_USE_HOST_PTR, r3.size() * sizeof(int), r3.data());
	
	long range_rooted = std::ceil(std::sqrt(range));
	int jump = 1048576;
	// Krok 3.1.
	for (long x = 0; x <= range_rooted / 2; x++){
		long limit = std::sqrt(range - 4*x*x);
		for(long y = 1; y <= limit; y += jump * 2){
			cl::Kernel kernel(program, "equation1");
			kernel.setArg(0, x);
			kernel.setArg(1, y/(jump*2));
			kernel.setArg(2, r1Buf);
			kernel.setArg(3, sieveBuf);
			kernel.setArg(4, range);
			queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1024, 1024, r1.size()));
		}
	}
	
	// Krok 3.2.
	for (long x = 0; x <= range_rooted / std::sqrt(3); x++){
		long limit = std::sqrt(range - 3*x*x);
		for(long y = !(x%2); y <= limit; y += jump * 2){
			cl::Kernel kernel(program, "equation2");
			kernel.setArg(0, x);
			kernel.setArg(1, y/(jump*2));
			kernel.setArg(2, r2Buf);
			kernel.setArg(3, sieveBuf);
			kernel.setArg(4, range);
			queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1024, 1024, r2.size()));
		}
	}

	// Krok 3.3.
	for (long x = 1; 2*x*x + 2*x - 1 < range; x++){
		long limit = 0;
		if(3*x*x > range)
			limit = std::ceil(std::sqrt(3*x*x - range));
		for(long y = x-1; y >= limit; y -= jump * 2){
			cl::Kernel kernel(program, "equation3");
			kernel.setArg(0, x);
			kernel.setArg(1, y/(jump*2));
			kernel.setArg(2, r3Buf);
			kernel.setArg(3, sieveBuf);
			kernel.setArg(4, range);
			queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(1024, 1024, r3.size()));
		}
	}	

	bool sieve[range];
	queue.enqueueReadBuffer(sieveBuf, CL_TRUE, 0, sizeof(sieve), sieve);

	for(long i = 6; i < range; i++){
		// Krok 4.
		// Pobierz z sita następną liczbę pierwszą
		if(sieve[i]){
			// Ktok 5.
			// Dodaj liczbę do listy liczb pierwszych i wyklucz wszystkie wielokrotności jej kwadratu
			primes.push_back(i);
			for(long j = i*i; j < range; j += i*i){
				sieve[j] = false;
			}
		}
	}

	// Koniec: wypisanie wartości
	//for (long n:primes){
	//	std::cout << n << std::endl;
	//}
}
