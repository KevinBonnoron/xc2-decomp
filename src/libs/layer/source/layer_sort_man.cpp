#include "layer/layer_sort_man.h"

#include "layer/layer_sort_obj.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerSortMan::~LayerSortMan() {
  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
}

void LayerSortMan::set2DSpace(LayerSortObj *object, u32 index) {
  if (index < unknown6c) {
    stock2DObj(object, index);
  } else {
    stock2DObj(object, unknown6c - 1);
  }
}

void LayerSortMan::stock2DObj(LayerSortObj *object, s32 index) {
  u32 flags = unknown30[index >> 5];
  u32 mask = 1 << (index & 0x1f);
  if (!(flags & mask)) {
    unknown30[index >> 5] = flags | mask;
    unknown10[index] = object;
  } else {
    unknown18[index]->unknown08 = object;
  }
  object->unknown08 = nullptr;
  unknown18[index] = object;
}

void LayerSortMan::stock3DObj(LayerSortObj *object, s32 index) {
  u32 flags = unknown38[index >> 5];
  u32 mask = 1 << (index & 0x1f);
  if (!(flags & mask)) {
    unknown38[index >> 5] = flags | mask;
    unknown20[index] = object;
  } else {
    unknown28[index]->unknown08 = object;
  }
  object->unknown08 = nullptr;
  unknown28[index] = object;
}

void LayerSortMan::alphaRender() {
  for (LayerSortObj *object = unknown40; object != nullptr; object = object->unknown08) {
    object->alphaRender();
  }
}

void LayerSortMan::lastRender() {
  for (LayerSortObj *object = unknown40; object != nullptr; object = object->unknown08) {
    object->lastRender();
  }
}

void LayerSortMan::finalRender() {
  for (LayerSortObj *object = unknown40; object != nullptr; object = object->unknown08) {
    object->finalRender();
  }
}

} // namespace layer
