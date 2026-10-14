#pragma once
#include "mm/mm_std_base.h"

namespace mm {
namespace mtl {

template <int LEN> class FixStr {
public:
  FixStr() {
    mData[0] = 0;
    m_nLen = 0;
  }

  FixStr &operator=(const char *string) {
    m_nLen = __builtin_strlen(string);
    __builtin_strcpy(mData, string);
    return *this;
  }

  FixStr &operator+=(const char *string) {
    int nBackLen = __builtin_strlen(string);
    // __LINE__ must be 487 as in the original header: it is the line argument of the assert.
#line 487
    MM_ASSERT(m_nLen + nBackLen < LEN);
    __builtin_strcat(mData, string);
    m_nLen += nBackLen;
    return *this;
  }

  void clear() {
    mData[0] = 0;
    m_nLen = 0;
  }

  void format(const char *format, ...);

  const char *c_str() const { return mData; }

private:
  char mData[LEN];
  int m_nLen;
};

} // namespace mtl
} // namespace mm
