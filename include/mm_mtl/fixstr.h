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

  FixStr(const char *pszName) { *this = pszName; }

  FixStr &operator=(const FixStr &string) { return *this = string.c_str(); }

  FixStr &operator=(const char *pszName) {
    // __LINE__ must be 219 and 221 as in the original header: they are the line arguments of the asserts.
#line 219
    MM_ASSERT(pszName != 0);
    m_nLen = __builtin_strlen(pszName);
    MM_ASSERT(m_nLen < LEN);
    __builtin_strcpy(mData, pszName);
    return *this;
  }

  FixStr &operator+=(const char *pszBack) {
    // __LINE__ must be 485 and 487 as in the original header: they are the line arguments of the asserts.
#line 485
    MM_ASSERT(pszBack != 0);
    int nBackLen = __builtin_strlen(pszBack);
    MM_ASSERT(m_nLen + nBackLen < LEN);
    __builtin_strcat(mData, pszBack);
    m_nLen += nBackLen;
    return *this;
  }

  void clear() {
    mData[0] = 0;
    m_nLen = 0;
  }

  void format(const char *format, ...);

  const char *c_str() const { return mData; }
  bool empty() const { return m_nLen == 0; }

private:
  char mData[LEN];
  int m_nLen;
};

} // namespace mtl
} // namespace mm
