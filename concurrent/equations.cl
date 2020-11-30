//Krok 3.1
__kernel void equation1(long x, long loop, __global bool* sieve, long range){
	int rests[] = {1, 13, 17, 29, 37, 41, 49, 53};
    long y = 1 + 2*(loop*1048576 + get_global_id(0)*1024 + get_global_id(1));
    long n = 4*x*x + y*y;
    int i = get_global_id(2);
    if(n < range){
        int r = n%60;
        if(r == rests[i])
            sieve[n] = !sieve[n];
    }
}

//Krok 3.2
__kernel void equation2(long x, long loop, __global bool* sieve, long range){
	int rests[] = {7, 19, 31, 43};
    long y = !(x%2) + 2*(loop*1048576 + get_global_id(0)*1024 + get_global_id(1));
    long n = 3*x*x + y*y;
    int i = get_global_id(2);
    if(n < range){
        int r = n%60;
        if(r == rests[i])
            sieve[n] = !sieve[n];
    }
}

//Krok 3.3
__kernel void equation3(long x, long loop, __global bool* sieve, long range){
    int rests[] = {11, 23, 47, 59};
    long y = x-1 - 2*(loop*1048576 + get_global_id(0)*1024 + get_global_id(1));
    if(y >= 0){
        long n = 3*x*x - y*y;
        int i = get_global_id(2);
        if(n < range){
            int r = n%60;
            if(r == rests[i])
                sieve[n] = !sieve[n];
        }
    }
}