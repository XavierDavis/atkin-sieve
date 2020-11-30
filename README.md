# Wersja sekwencyjna
Mocno usprawniona od pierwszej implementacji.
Przetestowana dla zasięgów do 16 000 000.

# Wersja równoległa
Działa dla zasięgów do 8 300 000.
Kilkadziesiąt razy wolniejsza od wersji sekwencyjnej.
Rozważana alternatywna implementacja, jeśli czas pozwoli.
## Usprawnienie #1
Reszty zdefiniowane w funkcjach kernelowych - jeden mniej globalny argument do przekazania kernelom.
Zmiana proporcji czasów user i sys, czas całkowity wykonania programu nieznacznie skrócony (dla zasięgo 8 000 000 poprawa z ~1,45 sekundy do ~1,3 sekundy).
## Usprawnienie #2
Zrównoleglenie fora zewnętrznego (iksów) zamiast wewnętrznego (igreków).
TODO
