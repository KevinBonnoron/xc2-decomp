#pragma once
#include <stddef.h>

#include "framework/manager_object.h"
#include "mm_mtl/singleton.h"

namespace layer {
class LayerManager;
} // namespace layer

namespace fw {

class LayerSetManager : public ManagerObject, public mm::mtl::PtrSingleton<LayerSetManager> {
public:
  LayerSetManager();
  bool initialize() override;
  bool finalize() override;
  void tail();
  void openDebugWindow();

  layer::LayerManager *unknown18; // Inferred role: layer manager; original member name unknown.
};

static_assert(offsetof(LayerSetManager, unknown18) == 0x18, "");

} // namespace fw
