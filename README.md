# Wersja sekwencyjna
## Debugging
### Obserwacje z prób zdebugowania kodu:
* Wszystkie niepoprawne liczby (w zakresie sitowania do 4 000 000) należą do pierwszej grupy reszt
* W kodzie nie udało się znaleźć żadnych błędów względem algorytmu
* Liczba niepoprawnych liczb pierwszych nie rośnie liniowo wraz z zasięgiem sitowania, tylko eksponencjalnie (może mieć związek z przekroczeniem rozmiaru zmiennej)
* Dotychczasowe próby zmieniania rozmiarów zmiennych (long int zamiast inta) zakończone niepowodzeniem
### Pomysły na debug:
* Napisanie skryptu shellowego sprawdzającego automatycznie do której grupy reszt należą niepoprawne wyniki z większych zasięgów sitowania
* Dalsze próby zmiany rozmiarów zmiennych
