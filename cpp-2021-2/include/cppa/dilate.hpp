#pragma once 

#include <numeric>

// Version 1 template
// Dilation par un element structurant horizontal centré de longueur de 2.k+1

template <class T,class BinaryOperation>
void dilate1d(image2d<T> in, image2d<T>, int k, BinaryOperation sup, T)
{
	const int alpha = 2 * k + 1;
	const int n = in.width();
	image2d<T> g = in;

	{
      int chunk_start = 0;
      int rem = n;

      for (; rem > 0; chunk_start += alpha, rem -= alpha)
      {
        int chunk_size = std::min(rem, alpha);
        std::partial_sum(&in(chunk_start / in.width(), chunk_start / in.height()), 
        				&in((chunk_start + chunk_size) / in.width(), (chunk_start + chunk_size) / in.height()), 
        				&g(chunk_start / g.width(), chunk_start / g.height()), 
        				sup);
      }
    }
}