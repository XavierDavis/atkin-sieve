# OPCJA PIERWSZA

### Kernel1
Krok 3.1

### Kernel2
Krok 3.2

### Kernel3
Krok 3.3

* Spodziewane przyspieszenie fragmentu kodu: trzykrotne
* Niewykorzystany potencjał karty graficznej

# OPCJA DRUGA

* Analogicznie do wersji sekwencyjnej, tylko odpalanie równoległe ~~1024~~ `1024*1024*(długość listy reszt)` operacji zamiast jednej w danej chwili
* Zrównoleglenie w zagnieżdżonym forze (igreków), w przeciwnym razie mogłoby dojść do naruszenia
* Spodziewane przyspieszenie fragmentu kodu: bardzo duże, przy idealnych warunkach `1024*1024*(długość listy reszt)`, ale pewnie będzie mniejsze
* Dobre wykorzystanie dostępnych zasobów karty graficznej (pełne dwa wymiary NDRange'a, częściowo wykorzystany trzeci)

## Rozpisanie pseudokodu
### W wersji sekwencyjnej:
```cpp
for(long x=0; x<limit1; x += s1){
    long limit2 = ...;
    for(long y=0; y<limit2; y += s2){
        long n = a*x*x + b*y*y;
        int r = n%60;

		//ten for jest zastąpiony przez ifa + std::find, ale w tej formie ułatwia rozpatrywanie wersji równoległej
        for(int i=0; i<rests.size(); i++)
            if(r == rests[i]){
                sieve[n] = !sieve[n];
                break;
            }
    }
}
```

### W wersji równoległej:
```cpp
for(long x=0; x<limit1; x += s1){
    long limit2 = ...;
    int jump = 1048576; //1024 * 1024
    for(long y=0; y<limit2; y += jump * s2){
        clEnqueueNDRangeKernel(command_queue, kernel, work_dim = 3, global_work_offset = null, global_work_size = {1024, 1024, rests.size()}, local_work_size);
        setArg(0, x); 				//przekazanie iksa, aby obliczyć n
        setArg(1, y/(jump*s2));		//przekazanie który to loop fora, aby można było bezproblemowo wyliczyć igrek dla konkretnego kernela
        setArg(2, rests);			//przekazanie tablicy reszt, globalne id trzeciego wymiaru służy za indeks
        setArg(3, sieve);			//przekazanie sita, aby kernele mogły edytować stosowne pozycje
        setArg(4, range);			//przekazanie zasięgu maksymalnego, jako porównania z n (y nie jest ograniczony w ten sam sposób co w wersji sekwencyjnej, prościej zrobić ograniczenie w samym kernelu)
    }
}
```
