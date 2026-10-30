#pragma once
#include <stddef.h>

#include "layer/layer_link_list.h"

namespace layer {

class LayerManager;
class LayerRceObj;

class LayerRceManager {
public:
  LayerRceManager(LayerManager *manager);
  ~LayerRceManager();
  LayerRceObj *createRceObj(const void *data, const char *name);
  void releaseObj(LayerRceObj *obj);
  void update();

  LayerManager *unknown00;                 // Inferred role: layer manager; original member name unknown.
  LayerLinkList<LayerRceObj> unknown08;    // Inferred role: object list; original member name unknown.
  LayerLinkList<LayerRceObj> unknown20[2]; // Inferred role: object lists per index; original member name unknown.
  LayerLinkList<LayerRceObj> unknown50;    // Inferred role: released object list; original member name unknown.
};

static_assert(offsetof(LayerRceManager, unknown08) == 0x08, "");
static_assert(offsetof(LayerRceManager, unknown20) == 0x20, "");
static_assert(offsetof(LayerRceManager, unknown50) == 0x50, "");
static_assert(sizeof(LayerRceManager) == 0x68, "");

} // namespace layer
