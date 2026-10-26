#pragma once
#include "mm_mtl/singleton.h"

namespace gmk {

template <typename T> class TGmkActiveList : public mm::mtl::PtrSingleton<TGmkActiveList<T>> {
public:
  TGmkActiveList() {}
  ~TGmkActiveList() override {}
};

} // namespace gmk
