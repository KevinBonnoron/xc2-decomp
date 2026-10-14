#pragma once

namespace mm {
namespace mtl {

class RTTI {
public:
  bool isKindOf(const RTTI *rtti) const;
};

template <typename T, typename U> T *dynamicCast(U *object) { return object->getRTTI()->isKindOf(&T::m_rtti) ? static_cast<T *>(object) : nullptr; }

} // namespace mtl
} // namespace mm
