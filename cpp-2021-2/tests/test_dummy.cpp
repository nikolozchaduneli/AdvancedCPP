#include <cppa/image.hpp>
#include <cppa/dilate.hpp>

#include <gtest/gtest.h>
#include <algorithm>

image2d<int> generate_iota(int w, int h)
{
  image2d<int> f(w, h);


  for (int y = 0; y < h; ++y)
  {
    for (int x = 0; x < w; ++x)
    {
      f(x, y) = w * y + x;
      //printf("%d\n", f(x, y));
    }
  }
  return f;
}


TEST(CPPA, test_dummy)
{
  auto f = generate_iota(10,10);
  ASSERT_EQ(f(5,5), 55);
}

TEST(CPPA, dilate)
{
  auto in = generate_iota(10,10);
  auto out = generate_iota(10,10);

  dilate1d(in, out, 5, [](auto a, auto b) { return std::max(a, b); }, 0);

  ASSERT_EQ(in(5,5), 55);
  ASSERT_NE(out(5,5), 55);
}

TEST(CPPA, erosion)
{
  auto in = generate_iota(10,10);
  auto out = generate_iota(10,10);

  dilate1d(in, out, 5, [](auto a, auto b) { return std::min(a, b); }, 0);

  ASSERT_EQ(in(5,5), 55);
  ASSERT_NE(out(5,5), 55);
}

TEST(CPPA, in_place_erosion)
{
  auto in = generate_iota(10,10);

  ASSERT_EQ(in(5,5), 55);

  dilate1d(in, in, 5, [](auto a, auto b) { return std::min(a, b); }, 0);

  ASSERT_NE(in(5,5), 55);
}

TEST(CPPA, dilate_V2)
{
  auto in = generate_iota(10,10);
  auto out = generate_iota(10,10);

  dilate1d(in, out, 5, false);

  ASSERT_EQ(in(5,5), 55);
  ASSERT_NE(out(5,5), 55);
}