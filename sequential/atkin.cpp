#include <iostream>
#include <list>
#include <map>
#include <utility>
#include <cmath>
#include <algorithm>

// Program realizujący sekwencyjną implementację sita Atkina

int main(){
	int range = 0;
	std::cin >> range;
	if(range < 6)
		exit(1);

	// Krok 1. Utworzenie listy wyników
	std::list<int> primes = {2, 3, 5};
	// Krok 2. Utworzenie listy reprezentującej sito
	std::map<int, bool> sieve;
	for(int i=6; i<range; i++){
		sieve.insert(std::pair<int, bool>(i, false));
	}
	
	// Podpunkty 3.1-3.3 można w teorii poprowadzić na dwa sposoby
	// 1. Albo iterować po wszystkich n i sprawdzać dla każdego z odpowiednią resztą wszystkie możliwe rozwiązania równania
	// 2. Albo sprawdzić dla wszystkich mających sens x i y jakie n mogą spełnić równanie i dla każdego z tych n sprawdzić resztę z dzielenia przez 60
	// Rozwiązanie równania ma dużo większą złożoność obliczeniową (O(n)) od sprawdzenia reszty z dzielenia przez 60 (O(1)), zatem sensowniejsze będzie rozwiązanie drugie

	int range_squared = std::ceil(std::sqrt(range));
	// Krok 3.1.
	// Równanie: 4x^2 + y^2 = n
	// 4x^2 jest zawsze parzyste, n ma być docelowo liczbą nieparzystą, y musi być zatem nieparzyste
	std::list<int> r1 = {1, 13, 17, 29, 37, 41, 49, 53};
	for (int x = 0; x <= range_squared; x++){
		for(int y = 1; y <= range_squared; y += 2){
			int n = 4*x*x + y*y;
			int r = n%60;
			if(std::find(r1.begin(), r1.end(), r) != r1.end())
				sieve[n] = !sieve[n];
		}
	}
	
	// Krok 3.2.
	// Równanie: 3x^2 + y^2 = n
	// 3x^2 jest parzyste tylko wtedy gdy x jest parzyste, zatem aby n było nieparzyste x i y muszą być różnej parzystości
	std::list<int> r2 = {7, 19, 31, 43};
	for (int x = 0; x <= range_squared; x++){
		for(int y = 0; y <= range_squared; y++){
			int n = 3*x*x + y*y;
			int r = n%60;
			if(std::find(r2.begin(), r2.end(), r) != r2.end())
				sieve[n] = !sieve[n];
		}
	}

	// Krok 3.3.
	// Równanie: 3x^2 - y^2 = n, gdzie x > y
	// 3x^2 jest parzyste tylko wtedy gdy x jest parzyste, zatem aby n było nieparzyste x i y muszą być różnej parzystości
	std::list<int> r3 = {11, 23, 47, 59};
	for (int x = 0; x <= range_squared; x++){
		for(int y = x-1; y >= 0; y -= 2){
			int n = 3*x*x - y*y;
			int r = n%60;
			if(std::find(r3.begin(), r3.end(), r) != r3.end())
				sieve[n] = !sieve[n];
		}
	}

	for(int i = 6; i < range; i++){
		// Krok 4.
		// Pobierz z sita następną liczbę pierwszą
		if(sieve[i]){
			// Ktok 5.
			// Dodaj liczbę do listy liczb pierwszych i wyklucz wszystkie wielokrotności jej kwadratu
			primes.push_back(i);
			for(int j = i*i; j < range; j += i*i){
				sieve[j] = false;
			}
		}
	}

	// Koniec: wypisanie wartości
	for (int n:primes){
		std::cout << n << std::endl;
	}
}
