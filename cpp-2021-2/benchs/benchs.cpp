#include <cppa/image.hpp>

#include <benchmark/benchmark.h>


void myiota(image2d<int> out)
{
  int w = out.width();
  int h = out.height();

  for (int y = 0; y < h; ++y)
    for (int x = 0; x < w; ++x)
      out(x,y) = w * y + x;
}


static void BM_Dummy(benchmark::State& state)
{
  int          n = state.range(0);
  image2d<int> out(n, n);

  for (auto _ : state)
    myiota(out);


  state.SetBytesProcessed(int64_t(state.iterations()) * int64_t(n * n));
}
BENCHMARK(BM_Dummy)->Arg(8)->Arg(64)->Arg(512)->Arg(1<<10);

// Write your benchmarks below following the same model as above
// You can check the documentation for more details
// https://github.com/google/benchmark/blob/master/README.md

BENCHMARK_MAIN();
