# Wersja sekwencyjna
Mocno usprawniona od pierwszej implementacji.
Przetestowana dla zasięgów do 16 000 000.

# Wersja równoległa
Działa dla zasięgów do 8 300 000.
Kilkadziesiąt razy wolniejsza od wersji sekwencyjnej.
Rozważana alternatywna implementacja, jeśli czas pozwoli.
## Usprawnienie #1
Reszty zdefiniowane w funkcjach kernelowych - jeden mniej globalny argument do przekazania kernelom.
Zmiana proporcji czasów user i sys, czas całkowity wykonania programu nieznacznie skrócony (dla zasięgu 8 000 000 poprawa z ~1,45 sekundy do ~1,3 sekundy).
## Usprawnienie #2
Zmiana konceptu zrównoleglenia: kroki 3.1, 3.2 i 3.3 zrównoleglone, zamiast równoległych obliczeń dla różnych y w poszczególnych krokach.
Poprawia to stosunek czasu obliczeń wewnętrznych do czasu dostępu do pamięci, ale w niesatysfakcjonującym stopniu (wersja równoległa nie jest efektywniejsza niż sekwencyjna).
Czas wykonania ~0.7-0.8 sekundy dla zasięgu 8 000 000.

