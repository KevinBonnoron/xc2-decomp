#pragma once
#include "mm_mtl/singleton.h"

namespace gf {

class GfMenuAdapter;

class GfMenuAdapterManager : public mm::mtl::PtrSingleton<GfMenuAdapterManager> {
public:
  static bool isAdapterFull();
  void addAdapter(GfMenuAdapter *adapter, bool isUpdateAfter);
  void setAfterUpdate(GfMenuAdapter *adapter);
};

} // namespace gf
