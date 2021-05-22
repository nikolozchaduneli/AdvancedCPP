#pragma once 

#include <numeric>



// Version 1 template
// Dilation par un element structurant horizontal centré de longueur de 2.k+1

template <class T,class BinaryOperation>
void dilate1d(image2d<T> &in, image2d<T> &out, int k, BinaryOperation sup, T)
{
	const int alpha = 2 * k + 1;
	const int n = in.width();
	
	for (int y = 0; y < in.height(); y++)
	{
		int chunk_start = 0;
      	int rem = n;

      	auto g = std::make_unique<T[]>(n); // Max-forward integral over the line
    	auto h = std::make_unique<T[]>(n); // Max-backward integral over the line

      	for (; rem > 0; chunk_start += alpha, rem -= alpha)
      	{
        	int chunk_size = std::min(rem, alpha);

        	std::partial_sum(&in(chunk_start, y), 
        				&in(chunk_start + chunk_size, y), 
        				&g[chunk_start], 
        				sup);
      	}

      	for (; rem > 0; chunk_start += alpha, rem -= alpha)
      	{
        	int chunk_size = std::min(alpha, rem);

        	std::partial_sum(std::make_reverse_iterator(&in(chunk_start,y)),
                         	 std::make_reverse_iterator(&in(chunk_start + chunk_size, y)),
                         	 std::make_reverse_iterator(&h[chunk_start]),
                         	 sup);
      	}

      	for (int i = 0; i < n; ++i)
      	{
        	out(i, y) = sup(h[i-k], g[i+k]);
      	}
	} 
}