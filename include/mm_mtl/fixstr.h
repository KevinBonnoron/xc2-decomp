#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include <stdarg.h>
#include <stdio.h>

namespace mm {
namespace mtl {

template <int LEN> class FixStr {
public:
  FixStr() {
    mData[0] = 0;
    m_nLen = 0;
  }

  FixStr(const char *pszName) { *this = pszName; }

  FixStr(const FixStr &string) { *this = string.c_str(); }

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

  FixStr operator+(const char *pszBack) const {
    FixStr result(c_str());
    result += pszBack;
    return result;
  }

  void clear() {
    mData[0] = 0;
    m_nLen = 0;
  }

  FixStr &format(const char *format, ...) {
    char buffer[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    *this = buffer;
    return *this;
  }

  void assign(const char *string, int len) {
    MM_ASSERT(len < LEN);
    __builtin_memcpy(mData, string, len);
    mData[len] = 0;
  }

  void erase(int pos, int count) {
    if (pos < m_nLen) {
      int end = pos + count < m_nLen ? pos + count : m_nLen;
      __builtin_strcpy(mData + pos, mData + end);
      m_nLen = __builtin_strlen(mData);
    }
  }

  // __LINE__ must be 715, 725 and 726 as in the original header: they are the line arguments of the asserts.
#line 714
  FixStr &insert(int index, const char *pszStr, int len) {
    MM_ASSERT(pszStr);
    int nowSize = m_nLen;
    int newSize = nowSize + len;
#line 725
    MM_ASSERT(newSize < capacity());
    MM_ASSERT(index <= nowSize);
    char *position = mData + index;
    move(position, nowSize - index, position + len);
    copy(pszStr, len, position);
    m_nLen = newSize;
    mData[newSize] = 0;
    return *this;
  }

  // __LINE__ must be 761 as in the original header: it is the line argument of the assert.
#line 760
  FixStr &replace(int pos, int count, const char *strNew) {
    MM_ASSERT(strNew);
    int len = __builtin_strlen(strNew);
    if (count == -1) {
      if (pos < m_nLen) {
        resize(pos);
      }
    } else {
      erase(pos, count);
    }
    insert(pos, strNew, len);
    return *this;
  }

  const char *c_str() const { return mData; }
  bool empty() const { return m_nLen == 0; }
  int capacity() const { return LEN - 1; }
  int length() const { return m_nLen; }

  void resize(int len) {
    mData[len] = 0;
    m_nLen = len;
  }

private:
  char mData[LEN];
  int m_nLen;
};

} // namespace mtl
} // namespace mm
