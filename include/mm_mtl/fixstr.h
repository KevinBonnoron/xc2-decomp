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

  // Inferred name; kept as an exception to the unknown-name rule (AGENTS.md): single-user helper whose existence only the match proves; rename if a sibling build gives a symbol.
  // By-value form of unknown001: the substring is built in the return slot. ml::PathUtil::getNoPathExtName (1.0.0: 0x710075b788, 103 instructions) returns the whole name
  // from one path (a copy: strlen, assertion 221, strcpy at 0x710075b880-0x710075b8b4) and the substring from the other, which it constructs in place (strb wzr, [x19] ;
  // str wzr, [x19, #0x40] at 0x710075b8cc, then strncpy into x19 at 0x710075b90c).
  // Forms tried without the helper, written in getNoPathExtName: a local `head` filled by unknown001 and returned (two returned locals, so the substring is built in a
  // local and copied: 116 instructions, frame 192 against the game's 128).
  FixStr substr(int s, int len) const {
    FixStr result;
    unknown001(result, s, len);
    return result;
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

  // Inferred role: index of the last occurrence of ch, -1 when missing (the game inlines it everywhere, 1.0.0: PathUtil::getFsaPath<FixStr<128>>
  // 0x7100169e4c, getNoExtName<FixStr<256>> 0x710019e430, changeExt 0x710075bd0c, GfMenuMapInfo::initialize 0x71003c5fb0, the lower-casing
  // helper of mm::mtl::unknown002, ScriptManager::makeFullPath 0x710019e240, GfDebugUtil::getSaveDataPath 0x71002cf75c...); no game symbol, original
  // name unknown. Documented exception per decision 55 of work/decisions-2026-11-14.md: the integer round trip below is allowed only in this helper.
  // The game's loop keeps `mData - 1` hoisted in one register (`sub x11, x19, #1 ; ldrb w13, [x11, x12]`, exit `add w12, w11, w12 ; sub w12, w12, w13`).
  // Three ingredients, each needed (forms tried: work/leftovers/oc-dec-fixstrsearch/FixStrSearch2_report.md, about 700 compiles):
  // 1. The base goes through an integer. The address SCEV `{(-1 + mData),+,-1}` merges the -1, LSR on AArch64 cannot fold reg + reg + imm and
  //    emits `add x9, x19, x8 ; ldurb [x9, #-1]`; only an SCEV-opaque base (a SCEVUnknown) is kept as one register. Every natural form (int, long,
  //    unsigned counters, `base[i]`, `s[i - 1]`, pointer or reverse-iterator loops, select or phi bases) gives the LSR form, a third counter or a csel.
  // 2. Accessors c_str()/length() rather than mData/m_nLen. A call in the found block keeps SimplifyCFG's two-entry-PHI folding from speculating the
  //    found block's `ptrtoint/sub/trunc` into the loop before the inliner runs (the second search, whose found edge goes into the join, otherwise
  //    keeps the arithmetic in the loop and LSR emits `add x12, x11, x10 ; ldrb [x12]`).
  // 3. A do-while behind the `length() != 0` guard. The second loop then has a preheader that falls through to its header, so early tail duplication
  //    keeps it and MachineLICM hoists the `mov w12, #-1` of the join phi into it; a for loop gives the `mov` after the loop and another char register.
  // Result, with this one helper: getFsaPath, getNoExtName, changeExt, GfMenuMapInfo::initialize, getMapInfoIndex, normalizeFileName,
  // makeFullPath and getSaveDataPath match byte for byte.
  int unknown004(char ch) const {
    if (length() != 0) {
      const char *base = reinterpret_cast<const char *>(reinterpret_cast<size_t>(c_str()) - 1);
      long i = length();
      do {
        const char *p = base + i;
        if (*p == ch) {
          return p - c_str();
        }
      } while (--i != 0);
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
  // Returns the string like insert and replace do: GfComEffectCaster::procMessageAsmCallback (1.0.0: 0x710050354c) assigns the result
  // back to the string (operator= from its own buffer: a second strlen and the assertion at line 221 after each erase). The game has no
  // out-of-line erase symbol, so the return type is chosen by that use only; `erase(...); s = s.c_str();` gives the same code.
  FixStr &erase(int pos, int count) {
    if (count == -1) {
      if (pos < m_nLen) {
        resize(pos);
      }
    } else if (pos < m_nLen) {
      int end = pos + count < m_nLen ? pos + count : m_nLen;
      __builtin_strcpy(mData + pos, mData + end);
      m_nLen = __builtin_strlen(mData);
    }
    return *this;
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
