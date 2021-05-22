#pragma once

#include <memory>
#include <cstdint>

enum pixel_format_t {
    UINT8, UINT16, UINT32, UINT64,
    INT8, INT16, INT32, INT64,
    FLOAT32, FLOAT64
};

template <class T> struct dtype_type;
template <> struct dtype_type<uint8_t>  { static constexpr pixel_format_t type = UINT8; };
template <> struct dtype_type<uint16_t> { static constexpr pixel_format_t type = UINT16; };
template <> struct dtype_type<uint32_t> { static constexpr pixel_format_t type = UINT32; };
template <> struct dtype_type<uint64_t> { static constexpr pixel_format_t type = UINT64; };
template <> struct dtype_type<int8_t>   { static constexpr pixel_format_t type = INT8; };
template <> struct dtype_type<int16_t>  { static constexpr pixel_format_t type = INT16; };
template <> struct dtype_type<int32_t>  { static constexpr pixel_format_t type = INT32; };
template <> struct dtype_type<int64_t>  { static constexpr pixel_format_t type = INT64; };
template <> struct dtype_type<float>    { static constexpr pixel_format_t type = FLOAT32; };
template <> struct dtype_type<double>   { static constexpr pixel_format_t type = FLOAT64; };

template <class T>
inline constexpr pixel_format_t dtype_t = dtype_type<T>::type;

class image2d_any
{
public:
  image2d_any(int width, int height, std::size_t size, pixel_format_t dtype);


  void*          operator()(int x, int y) noexcept { return (void*)(m_buffer + y * m_pitch + x * m_size); }
  int            width() const noexcept { return m_width; }
  int            height() const noexcept { return m_width; }
  pixel_format_t dtype() const noexcept { return m_dtype; }

protected:
  std::shared_ptr<std::byte[]> m_data;
  int                          m_width, m_height;
  std::byte*                   m_buffer;
  std::ptrdiff_t               m_pitch, m_size;
  pixel_format_t               m_dtype;
};


template <class T>
class image2d : public image2d_any
{
public:
  image2d(int width, int height)
    : image2d_any(width, height, sizeof(T), dtype_t<T>)
  {
  }

  T& operator()(int x, int y) noexcept { return ((T*)m_buffer)[y * m_width + x]; }
  T  operator()(int x, int y) const noexcept { return ((T*)m_buffer)[y * m_width + x]; }
};
