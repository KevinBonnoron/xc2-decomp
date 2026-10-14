#pragma once

namespace mm {
namespace mtl {

template <int N> class FixStr {
public:
  FixStr &operator=(const char *string) {
    mLength = __builtin_strlen(string);
    __builtin_strcpy(mData, string);
    return *this;
  }

  void format(const char *format, ...);

private:
  char mData[N];
  int mLength;
};

} // namespace mtl
} // namespace mm
