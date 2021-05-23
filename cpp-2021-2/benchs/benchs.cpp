#include <cppa/image.hpp>
#include <cppa/dilate.hpp>

#include <benchmark/benchmark.h>

void myiota(image2d<int> out)
{
  int w = out.width();
  int h = out.height();

  for (int y = 0; y < h; ++y)
    for (int x = 0; x < w; ++x)
      out(x,y) = w * y + x;
}

auto f = image2d<int>(10,10);
myiota(f);

static void BM_Dummy(benchmark::State& state)
{
  int          n = state.range(0);
  image2d<int> out(n, n);

  for (auto _ : state)
    dilate1d(f, f, 5, [](auto a, auto b) { return std::max(a, b); }, 0);


  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(n * n));
}
BENCHMARK(BM_Dummy)->Arg(8)->Arg(64)->Arg(512)->Arg(1<<10);

// Write your benchmarks below following the same model as above
// You can check the documentation for more details
// https://github.com/google/benchmark/blob/master/README.md

static void BM_Dummy_2(benchmark::State& state)
{
  int n = state.range(0);
  image2d<int> out(n, n);

  for (auto _ : state)
    myiota(out);


  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(n * n));
}
BENCHMARK(BM_Dummy_2)->Arg(8*2)->Arg(64*2)->Arg(512*2)->Arg(1<<11);

BENCHMARK_MAIN();