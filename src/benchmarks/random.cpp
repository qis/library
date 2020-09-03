#include <benchmark/benchmark.h>
#include <library/random.hpp>

static void random(benchmark::State& state)
{
  for (auto _ : state) {
    const auto str = library::random();
    benchmark::DoNotOptimize(str);
  }
}
BENCHMARK(random);
