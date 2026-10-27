#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerManager;
class LayerRceObj;

class LayerRceManager {
public:
  struct unknown001 {
    LayerRceObj *unknown00; // Inferred role: first node; original member name unknown.
    LayerRceObj *unknown08; // Inferred role: last node; original member name unknown.
    s32 unknown10;          // Inferred role: node count; original member name unknown.
  };

  ~LayerRceManager();
  void releaseObj(LayerRceObj *obj);
  void update();

  LayerManager *unknown00; // Inferred role: layer manager; original member name unknown.
  unknown001 unknown08;    // Inferred role: object list; original member name unknown.
  unknown001 unknown20[2]; // Inferred role: object lists per index; original member name unknown.
  unknown001 unknown50;    // Inferred role: object list; original member name unknown.
};

static_assert(offsetof(LayerRceManager, unknown08) == 0x08, "");
static_assert(offsetof(LayerRceManager, unknown20) == 0x20, "");
static_assert(offsetof(LayerRceManager, unknown50) == 0x50, "");
static_assert(sizeof(LayerRceManager) == 0x68, "");

} // namespace layer
