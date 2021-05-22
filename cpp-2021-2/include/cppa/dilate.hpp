#pragma once 

template <class T,class BinaryOperation>
void dilate1d(image2d<T> in, image2d<T> out, int k, BinaryOperation sup, T zero);