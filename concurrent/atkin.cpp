#define CL_TARGET_OPENCL_VERSION 120

#include <CL/cl.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>

int main(){

	//----------------------------------------------------------------------INICJALIZACJA OPENCLA
	//Pobranie platform
	std::vector<cl::Platform> platforms;
	cl::Platform::get(&platforms);

	//Pobranie urządzeń
	cl::Platform platform = platforms.front();
	std::vector<cl::Device> devices;
	platform.getDevices(CL_DEVICE_TYPE_ALL, &devices);
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
	//Utworzenie kolejek
	cl::CommandQueue queue1(context, device);
	cl::CommandQueue queue2(context, device);
	cl::CommandQueue queue3(context, device);
	//----------------------------------------------------------------------INICJALIZACJA OPENCLA

	long range = 0;
	std::cin >> range;
	if(range < 6)
		exit(1);

	auto start = std::chrono::high_resolution_clock::now();
	// Krok 1. Utworzenie listy wyników
	std::vector<long> primes = {2, 3, 5};
	// Krok 2. Utworzenie bufora OpenCLowego reprezentującego sito
	cl::Buffer sieveBuf(context, CL_MEM_READ_WRITE|CL_MEM_HOST_READ_ONLY, sizeof(int) * range);

	// Uruchomienie obliczeń dla pierwszej grupy reszt
	cl::Kernel kernel1(program, "equation1");
	kernel1.setArg(0, sieveBuf);
	kernel1.setArg(1, range);
	queue1.enqueueTask(kernel1);
	
	// Równolegle druga grupa reszt
	cl::Kernel kernel2(program, "equation2");
	kernel2.setArg(0, sieveBuf);
	kernel2.setArg(1, range);
	queue2.enqueueTask(kernel2);

	// Równolegle trzecia grupa reszt
	cl::Kernel kernel3(program, "equation3");
	kernel3.setArg(0, sieveBuf);
	kernel3.setArg(1, range);
	queue3.enqueueTask(kernel3);

	// Czekanie na zakończenie zadań
	cl::finish();

	// Odczyt z bufora
	bool sieve[range];
	queue1.enqueueReadBuffer(sieveBuf, CL_TRUE, 0, sizeof(sieve), sieve);

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

	auto end = std::chrono::high_resolution_clock::now();
	double time_count = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();
	time_count *= 1e-9;
	std::cout << "Algorytm zajął " << time_count << " s" << std::endl;

	// Koniec: wypisanie wartości
	//for (long n:primes){
	//	std::cout << n << std::endl;
	//}
}
