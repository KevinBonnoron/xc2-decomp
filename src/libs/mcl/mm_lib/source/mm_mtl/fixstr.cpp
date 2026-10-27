#include "mm_mtl/fixstr.h"

namespace mm {
namespace mtl {

template FixStr<4> &FixStr<4>::format(const char *format, ...);
template FixStr<20> &FixStr<20>::format(const char *format, ...);
template FixStr<24> &FixStr<24>::format(const char *format, ...);
template FixStr<512> &FixStr<512>::format(const char *format, ...);
template FixStr<64> &FixStr<64>::insert(int index, const char *pszStr, int len);
template FixStr<256> &FixStr<256>::insert(int index, const char *pszStr, int len);
template FixStr<64> &FixStr<64>::replace(int pos, int count, const char *strNew);
template FixStr<16> FixStr<16>::operator+(const char *pszBack) const;
template FixStr<256> FixStr<256>::operator+(const char *pszBack) const;

} // namespace mtl
} // namespace mm
