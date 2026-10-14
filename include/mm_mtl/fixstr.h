#pragma once

namespace mm {
namespace mtl {

template <int N> class FixStr {
public:
  void format(const char *format, ...);

private:
  char mData[N];
};

} // namespace mtl
} // namespace mm
