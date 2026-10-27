#include "mm_mtl/vector.h"

#include <utility> // IWYU pragma: keep

#include "mm_mtl/fixstr.h" // IWYU pragma: keep

namespace mm {
namespace mtl {

template void Vector<bool>::expand(size_t, size_t);
template void Vector<FixStr<256>>::expand(size_t, size_t);
template void Vector<FixStr<256>>::push_back(const FixStr<256> &);
template void Vector<std::pair<int, float>>::expand(size_t, size_t);
template void Vector<bool>::extend(size_t, size_t);
template void Vector<bool>::resize(size_t);
template void Vector<float>::expand(size_t, size_t);
template void Vector<float>::extend(size_t, size_t);
template void Vector<float>::resize(size_t);
template void Vector<const char *>::expand(size_t, size_t);
template void Vector<signed char>::expand(size_t, size_t);
template void Vector<unsigned short>::expand(size_t, size_t);
template void Vector<void *>::expand(size_t, size_t);
template void Vector<bool>::extend(size_t, size_t, const bool &);
template void Vector<bool>::resize(size_t, const bool &);
template void Vector<short>::assign(const Vector<short> &);

} // namespace mtl
} // namespace mm
