#pragma once

namespace mm {
namespace mtl {

template <int N> class FixStr {
public:
  FixStr() {
    mData[0] = 0;
    mLength = 0;
  }

  FixStr &operator=(const char *string) {
    mLength = __builtin_strlen(string);
    __builtin_strcpy(mData, string);
    return *this;
  }

  void format(const char *format, ...);

  const char *c_str() const { return mData; }

private:
  char mData[N];
  int mLength;
};

} // namespace mtl
} // namespace mm
