#include <vector>
#include <random>

#include <benchmark/benchmark.h>

#include "InversionCount.hpp"

using namespace std;

static void InversionCount(benchmark::State& state) {
    random_device rng;
    mt19937 mersenne(rng());

    vector<int64_t> input(state.range(0));
    for(size_t i = 0; i < input.size(); i++)
        input[i] = i + 1;

    shuffle(input.begin(), input.end(), mersenne);

    for(auto _ : state) {
        inversion_count(input);
    }
}

BENCHMARK(InversionCount)->DenseRange(1, 1024, 1)
                         ->DenseRange(1024+512, 65535-512, 512)
                         ->RangeMultiplier(2)->Range(65535, 1<<25);
BENCHMARK_MAIN();
