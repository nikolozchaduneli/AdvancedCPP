#pragma once 

#include <cppa/image.hpp>

#include <numeric>
#include <cassert>
#include <cstdint>
#include <cfloat>
#include "asmjit/src/asmjit/asmjit.h"

typedef int (*Func)(void);

using namespace asmjit;

// Version 1 template
// Dilation par un element structurant horizontal centré de longueur de 2.k+1

template <class T,class BinaryOperation>
void dilate1d(image2d<T> &in, image2d<T> &out, int k, BinaryOperation sup, T zero)
{
    (void) zero;
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

        rem = n;
        chunk_start = 0;

        for (; rem > 0; chunk_start += alpha, rem -= alpha)
        {
            int chunk_size = std::min(alpha, rem);

            std::partial_sum(std::make_reverse_iterator(&in(chunk_start + chunk_size,y)),
                             std::make_reverse_iterator(&in(chunk_start, y)),
                             std::make_reverse_iterator(&h[chunk_start + chunk_size]),
                             sup);
        }

        for (int i = 0; i < n; ++i)
        {
            out(i, y) = sup(h[i-k], g[i+k]);
        }
    } 
}

// Version 2 dynamique qui dispatche vers la V1 => code bloat
void dilate1d(image2d_any in, image2d_any out, int k, bool decreasing)
{
    pixel_format_t dtype = in.dtype();
    assert(dtype == out.dtype());

    if(decreasing) // erosion
    {
        switch(dtype)
        {
            case UINT8: dilate1d( (image2d<uint8_t>&)in, (image2d<uint8_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, (unsigned char)UINT8_MAX); break;
            case UINT16: dilate1d( (image2d<uint16_t>&)in, (image2d<uint16_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, (short unsigned int)UINT16_MAX); break;
            case UINT32: dilate1d( (image2d<uint32_t>&)in, (image2d<uint32_t>&)out, k,  [](auto a, auto b) { return std::min(a, b); }, (unsigned int)UINT32_MAX); break;
            case UINT64: dilate1d( (image2d<uint64_t>&)in, (image2d<uint64_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, (unsigned long)UINT64_MAX); break;
            case INT8: dilate1d( (image2d<int8_t>&)in, (image2d<int8_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, (signed char)INT8_MAX); break;
            case INT16: dilate1d( (image2d<int16_t>&)in, (image2d<int16_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, (short int)INT16_MAX); break;
            case INT32: dilate1d( (image2d<int32_t>&)in, (image2d<int32_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, INT32_MAX); break;
            case INT64: dilate1d( (image2d<int64_t>&)in, (image2d<int64_t>&)out, k, [](auto a, auto b) { return std::min(a, b); }, INT64_MAX); break;
            case FLOAT32: dilate1d( (image2d<float>&)in, (image2d<float>&)out, k, [](auto a, auto b) { return std::min(a, b); }, FLT_MAX); break;
            case FLOAT64: dilate1d( (image2d<double>&)in, (image2d<double>&)out, k, [](auto a, auto b) { return std::min(a, b); }, DBL_MAX); break;
        }
    }
    
    else
    {
        switch(dtype)
        {
            case UINT8: dilate1d( (image2d<uint8_t>&)in, (image2d<uint8_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, (unsigned char)UINT8_MAX); break;
            case UINT16: dilate1d( (image2d<uint16_t>&)in, (image2d<uint16_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, (short unsigned int)UINT16_MAX); break;
            case UINT32: dilate1d( (image2d<uint32_t>&)in, (image2d<uint32_t>&)out, k,  [](auto a, auto b) { return std::max(a, b); }, (unsigned int)UINT32_MAX); break;
            case UINT64: dilate1d( (image2d<uint64_t>&)in, (image2d<uint64_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, (unsigned long)UINT64_MAX); break;
            case INT8: dilate1d( (image2d<int8_t>&)in, (image2d<int8_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, (signed char)INT8_MAX); break;
            case INT16: dilate1d( (image2d<int16_t>&)in, (image2d<int16_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, (short int)INT16_MAX); break;
            case INT32: dilate1d( (image2d<int32_t>&)in, (image2d<int32_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, INT32_MAX); break;
            case INT64: dilate1d( (image2d<int64_t>&)in, (image2d<int64_t>&)out, k, [](auto a, auto b) { return std::max(a, b); }, INT64_MAX); break;
            case FLOAT32: dilate1d( (image2d<float>&)in, (image2d<float>&)out, k, [](auto a, auto b) { return std::max(a, b); }, FLT_MAX); break;
            case FLOAT64: dilate1d( (image2d<double>&)in, (image2d<double>&)out, k, [](auto a, auto b) { return std::max(a, b); }, DBL_MAX); break;
        }
    }
}

/*
// Version 3 dynamique avec code généré avec ASM Jit
void dilate1dV3(image2d_any in, image2d_any out, int k, bool decreasing)
{
    JitRuntime rt;

    CodeHolder code;
    code.init(rt.environment());
    x86::Assembler a(&code);

    a.mov(x86::eax, dilate1d(in, out, k, decreasing));
    a.ret();

    Func fn
    Error err = rt.add(&fn, &code);

    if (err) 
    {
        printf("AsmJit failed: %s\n", DebugUtils::errorAsString(err));
        return;
    }

    fn();

    rt.release(fn);
}
*/