#include <iostream>
#include <list>
#include <map>
#include <cmath>

// Program realizujący sekwencyjną implementację sita Erastotenesa, napisany w celu porównywania wyników z sitem Atkina

int main(){
	int range = 0;
	std::cin >> range;
	if(range < 6)
		exit(1);

	std::list<int> primes = {2};
	std::map<int, bool> sieve;
	for(int i=2; i<range; i++){
		sieve.insert(std::pair<int, bool>(i, true));
	}

	for(int i=2; i< std::sqrt(range); i++){
		if(sieve[i])
			for(int j = i*i; j < range; j += i)
				sieve[j] = false;
	}
	for(int i=2; i<range; i++)
		if(sieve[i])
			std::cout << i << std::endl;
}
