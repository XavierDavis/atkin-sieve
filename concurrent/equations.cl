//Krok 3.1
__kernel void equation1(__global bool* sieve, long range){
	int rests[] = {1, 13, 17, 29, 37, 41, 49, 53};
    float limit1 = ceil(sqrt((float)range))/2;
    float limit2;
	for(long x = 0; x <= limit1; x++){
        limit2 = sqrt((float)(range - 4*x*x));
        for(long y = 1; y <= limit2; y += 2){
            long n = 4*x*x + y*y;
            int r = n%60;
            for(int i=0; i<8; i++){
                if(r == rests[i])
                    sieve[n] = !sieve[n];
            }
        }
    }
}
//Krok 3.2
__kernel void equation2(__global bool* sieve, long range){
	int rests[] = {7, 19, 31, 43};
    float limit1 = ceil(sqrt((float)range)) / sqrt(3.0);
    float limit2;
    for(long x = 0; x <= limit1; x++){
        limit2 = sqrt((float)(range - 3*x*x));
        for(long y = !(x%2); y <= limit2; y += 2){
            long n = 3*x*x + y*y;
            int r = n%60;
            for(int i=0; i<4; i++){
                if(r == rests[i])
                    sieve[n] = !sieve[n];
            }
        }
    }
}
//Krok 3.3
__kernel void equation3(__global bool* sieve, long range){
    int rests[] = {11, 23, 47, 59};
    float limit = 0;
	for (long x = 0; 2*x*x + 2*x - 1 < range; x++){
        limit = ceil(sqrt((float)(3*x*x - range))) * (3*x*x > range); //zamiast ifa
        for(long y = x-1; y >= limit; y -= 2){
            long n = 3*x*x - y*y;
            int r = n%60;
            for(int i=0; i<4; i++){
                if(r == rests[i])
                    sieve[n] = !sieve[n];
            }
        }
    }
}