//Krok 3.1
__kernel void equation1(long x, long loop, __global int* rests, __global bool* sieve, long range){
    long y = 1 + 2*(loop*1048576 + get_global_id(0)*1024 + get_global_id(1));
    long n = 4*x*x + y*y;
    int i = get_global_id(3);
    if(n < range){
        int r = n%60;
        if(r == rests[i])
            sieve[n] = !sieve[n];
    }
}

//Krok 3.2
__kernel void equation2(long x, long loop, __global int* rests, __global bool* sieve, long range){
    long y = !(x%2) + 2*(loop*1048576 + get_global_id(0)*1024 + get_global_id(1));
    long n = 3*x*x + y*y;
    int i = get_global_id(3);
    if(n < range){
        int r = n%60;
        if(r == rests[i])
            sieve[n] = !sieve[n];
    }
}

//Krok 3.3
__kernel void equation3(long x, long loop, __global int* rests, __global bool* sieve, long range){
    long y = x-1 - 2*(loop*1048576 + get_global_id(0)*1024 + get_global_id(1));
    if(y >= 0){
        long n = 3*x*x - y*y;
        int i = get_global_id(3);
        if(n < range){
            int r = n%60;
            if(r == rests[i])
                sieve[n] = !sieve[n];
        }
    }
}