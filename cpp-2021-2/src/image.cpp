#include <cppa/image.hpp>

image2d_any::image2d_any(int width, int height, std::size_t size, pixel_format_t dtype)
{
  m_data.reset(new std::byte[width * height * size]);
  m_buffer = m_data.get();
  m_width  = width;
  m_height = height;
  m_size   = size;
  m_pitch  = width * size;
  m_dtype  = dtype;
}