# Inversions Count Benchmark

We propose four approaches and solutions to this problem and benchmark them using [Google Benchmark](https://github.com/google/benchmark):

1. Using Merge sort
2. Using Binary balanced trees (AVL trees implemented with pointers)
3. Using Binary balanced trees (AVL trees implemented with `std::vector`)
4. Using Fenwick trees (`std::vector` implementation)

The first approach is a standard solution to this problem. Comparing (2) and (3) allows us to compare how the use of pointers and frequent memory allocations can affect cache efficiency and thus degrade performance. Finally, the use of Fenwick trees in solution (4) allows us to test and benchmark a completely different approach which uses an underlying vector with no concrete tree being constructed (similarly as heaps).

The Fenwick tree solution has also been tested on randomly generated permutations in order to verify how much the sorting and remapping overhead can affect the overall performance. The remapping uses the `std::sort` function available from the STL.

## Methodological notes

All tests have been verified by randomly generating data and testing all the solutions on the same datasets, with progressively increasing input dimension. The input dimension is linear until size 1024 to check for early overheads, then increases in blocks of 512 until size 65536 in order to interpolate a starting complexity representation. Finally, we tested by exponentially increasing array size using powers of two.

Multiple iterations of each test are automatically performed by [Google Benchmark](https://github.com/google/benchmark) and then averaged together in order to smooth down the systematic error.

All tested code is available on this repository and all solutions have been tested on the [SPOJ page of the problem](https://www.spoj.com/problems/INVCNT/).

# Results

## Size 1-1024, linear increase by 1

![Linear increase 1-1024](results/1024.png)

## Size 1-65536, linear increase by 512

![1024-65536, increase by 512](results/65536.png)

## Size from 65536, exponential increase by 2

![65536, double up](results/all.png)

## Overtaking of `merge` over `fenwick-perm`

![Overtake of `merge` over `fenwick-perm`](results/overtake.png)

# Specs

Compiled with `g++ -O3`, gcc version 8.3.0 (Debian 8.3.0-6), [Google Benchmark](https://github.com/google/benchmark) 1.5.2, tested on a Intel(R) Core(TM) i7-7500U CPU @ 2.70 GHz / 2.90 GHz, 4 cores using WSL2.
