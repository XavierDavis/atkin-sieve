# Atkin sieve
The goal of this project was to improve the effectiveness of Atkin sieve algorithm by making the calculations concurrent using OpenCL. It wasn't quite reached because of excessive access to global memory, however I've decided to keep the repository up for now, as I believe it to be one of my first decently written pieces of code.

The project covers:
- sequential versions of Eratosthenes sieve and Atkin sieve written in c++ and a shell script to verify the correctness of the latter (using results from the former)
- a concurrent version of Atkin sieve written in c++ and OpenCL, and a shell script to verify its correctness (using results from the sequential version)
- a shell script to compare the time efficiency of sequential and concurrent versions of Atkin sieve and write the results to a text file
