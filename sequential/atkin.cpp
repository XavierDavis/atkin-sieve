#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

// Program realizujący sekwencyjną implementację sita Atkina

int main(){
	long range = 0;
	std::cin >> range;
	if(range < 6)
		exit(1);

	// Krok 1. Utworzenie listy wyników
	std::vector<long> primes = {2, 3, 5};
	// Krok 2. Utworzenie listy reprezentującej sito
	std::vector<bool> sieve(range, false);

	// Podpunkty 3.1-3.3 można w teorii poprowadzić na dwa sposoby
	// 1. Albo iterować po wszystkich n i sprawdzać dla każdego z odpowiednią resztą wszystkie możliwe rozwiązania równania
	// 2. Albo sprawdzić dla wszystkich mających sens x i y jakie n mogą spełnić równanie i dla każdego z tych n sprawdzić resztę z dzielenia przez 60
	// Rozwiązanie równania ma dużo większą złożoność obliczeniową (O(n)) od sprawdzenia reszty z dzielenia przez 60 (O(1)), zatem sensowniejsze będzie rozwiązanie drugie

	long range_rooted = std::ceil(std::sqrt(range));
	// Krok 3.1.
	// Równanie: 4x^2 + y^2 = n
	// 4x^2 jest zawsze parzyste, n ma być docelowo liczbą nieparzystą, y musi być zatem nieparzyste
	std::vector<int> r1 = {1, 13, 17, 29, 37, 41, 49, 53};
	for (long x = 0; x <= range_rooted / 2; x++){
		long limit = std::sqrt(range - 4*x*x);
		for(long y = 1; y <= limit; y += 2){
			long n = 4*x*x + y*y;
			int r = n%60;
			if(std::find(r1.begin(), r1.end(), r) != r1.end())
				sieve[n] = !sieve[n];
		}
	}
	
	// Krok 3.2.
	// Równanie: 3x^2 + y^2 = n
	// 3x^2 jest parzyste tylko wtedy gdy x jest parzyste, zatem aby n było nieparzyste x i y muszą być różnej parzystości
	std::vector<int> r2 = {7, 19, 31, 43};
	for (long x = 0; x <= range_rooted / std::sqrt(3); x++){
		long limit = std::sqrt(range - 3*x*x);
		for(long y = !(x%2); y <= limit; y += 2){
			long n = 3*x*x + y*y;
			int r = n%60;
			if(std::find(r2.begin(), r2.end(), r) != r2.end())
				sieve[n] = !sieve[n];
		}
	}

	// Krok 3.3.
	// Równanie: 3x^2 - y^2 = n, gdzie x > y
	// 3x^2 jest parzyste tylko wtedy gdy x jest parzyste, zatem aby n było nieparzyste x i y muszą być różnej parzystości
	std::vector<int> r3 = {11, 23, 47, 59};
	for (long x = 0; 2*x*x + 2*x - 1 < range; x++){
		long limit = 0;
		if(3*x*x > range)
			limit = std::ceil(std::sqrt(3*x*x - range));
		for(long y = x-1; y >= limit; y -= 2){
			long n = 3*x*x - y*y;
			int r = n%60;
			if(std::find(r3.begin(), r3.end(), r) != r3.end())
				sieve[n] = !sieve[n];
		}
	}

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
	for (long n:primes){
		std::cout << n << std::endl;
	}
}
