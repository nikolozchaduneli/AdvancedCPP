#include <cppa/image.hpp>
#include <cppa/dilate.hpp>

// Version 1 template
// Dilation par un element structurant horizontal centré de longueur de 2.k+1
template <class T,class BinaryOperation>
void dilate1d(image2d<T> in, image2d<T> out, int k, BinaryOperation sup, T zero)
{
	return;
}