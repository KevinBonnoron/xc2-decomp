#pragma once
#include "mm/mm_std_base.h"
#include "mm_mtl/algorithm.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

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

  // Inferred role: copies len characters from position s into dest; no game symbol, original name unknown.
  void unknown001(FixStr &dest, int s, int len) const {
    // __LINE__ must be 462 as in the original header: it is the line argument of the assert.
#line 462
    MM_ASSERT(s < m_nLen && s + len <= m_nLen);
    __builtin_strncpy(dest.mData, mData + s, len);
    dest.mData[len] = 0;
    dest.m_nLen = __builtin_strlen(dest.mData);
  }

  // Inferred role: index of the first occurrence of a substring at or after start, -1 when missing; no game symbol, original name unknown. Shape from
  // fw::ResourceManager::isDelayReleaseExtention (1.0.0: 0x710019c128), which compares at each position with strncmp, and from
  // mm::mtl::replacestr (0x71001a86e0), which searches again from the end of each replacement.
  int unknown003(const char *pszStr, int start = 0) const {
    int len = __builtin_strlen(pszStr);
    for (int i = start; i < m_nLen; i++) {
      if (strncmp(mData + i, pszStr, len) == 0) {
        return i;
      }
    }
    return -1;
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

  // A count of -1 erases up to the end (mm::mtl::replacestr inlines this test with the count it passes, 1.0.0: 0x71001a86e0).
  void erase(int pos, int count) {
    if (count == -1) {
      if (pos < m_nLen) {
        resize(pos);
      }
    } else if (pos < m_nLen) {
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

  // __LINE__ must be 686 and 687 as in the original header: they are the line arguments of the asserts.
#line 685
  FixStr &insert(int index, int count, char ch) {
    if (index < 0) {
      index = 0;
    }
    int nowSize = m_nLen;
    int newSize = nowSize + count;
    MM_ASSERT(newSize < capacity());
    MM_ASSERT(index <= nowSize);
    char *position = mData + index;
    move(position, m_nLen - index, position + count);
    fill_n(position, count, ch);
    m_nLen = newSize;
    mData[newSize] = 0;
    return *this;
  }

  // __LINE__ must be 761 as in the original header: it is the line argument of the assert.
#line 760
  FixStr &replace(int pos, int count, const char *strNew) {
    MM_ASSERT(strNew);
    int len = __builtin_strlen(strNew);
    erase(pos, count);
    insert(pos, strNew, len);
    return *this;
  }

  const char *c_str() const { return mData; }
  char &operator[](int index) { return mData[index]; }

  // Inferred role: element access with a bounds assert; no game symbol, original name unknown.
  // __LINE__ must be 302 as in the original header: it is the line argument of the assert.
#line 301
  char &unknown002(int nIdx) {
    MM_ASSERT(nIdx < m_nLen);
    return mData[nIdx];
  }
  bool operator<(const FixStr &rhs) const { return strcmp(mData, rhs.mData) < 0; }
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
