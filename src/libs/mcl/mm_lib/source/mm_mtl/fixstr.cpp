#include "mm_mtl/fixstr.h"

#include "mm_mtl/map.h" // IWYU pragma: keep

namespace mm {
namespace mtl {

template FixStr<4> &FixStr<4>::format(const char *format, ...);
template FixStr<20> &FixStr<20>::format(const char *format, ...);
template FixStr<24> &FixStr<24>::format(const char *format, ...);
template FixStr<512> &FixStr<512>::format(const char *format, ...);
template FixStr<64> &FixStr<64>::insert(int index, const char *pszStr, int len);
template FixStr<256> &FixStr<256>::insert(int index, const char *pszStr, int len);
template FixStr<256> &FixStr<256>::insert(int index, int count, char ch);
template FixStr<64> &FixStr<64>::replace(int pos, int count, const char *strNew);
template FixStr<16> FixStr<16>::operator+(const char *pszBack) const;
template FixStr<256> FixStr<256>::operator+(const char *pszBack) const;
template Map<FixStr<64>, int>::tree_type::node *Map<FixStr<64>, int>::tree_type::insert(const MapPair<FixStr<64>, int> &value);
template void Map<FixStr<64>, int>::tree_type::free_node(Map<FixStr<64>, int>::tree_type::node *target, bool recursive);
template void Map<FixStr<64>, int>::tree_type::rebalance(Map<FixStr<64>, int>::tree_type::node *new_node);

} // namespace mtl
} // namespace mm
