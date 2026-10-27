#include "layer/layer_sort_man.h"

#include <string.h>

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

void LayerSortMan::begin(const mm::Vec3 &position) {
  s32 total = unknown74 + unknown78;
  s32 padding = (32 - total % 32) % 32;
  memset(unknown30, 0, total + padding);
  unknown50 = position;
  unknown40 = nullptr;
  unknown48 = nullptr;
}

void LayerSortMan::end() {
  for (u32 i = 0; i < unknown70; i++) {
    if (unknown38[i >> 5] & (1 << (i & 0x1f))) {
      if (unknown40 == nullptr) {
        unknown40 = unknown20[i];
      } else {
        LayerSortObj *last = unknown48;
        last->unknown08 = unknown20[i];
      }
      unknown48 = unknown28[i];
    }
  }
  for (u32 i = 0; i < unknown6c; i++) {
    if (unknown30[i >> 5] & (1 << (i & 0x1f))) {
      if (unknown40 == nullptr) {
        unknown40 = unknown10[i];
      } else {
        LayerSortObj *last = unknown48;
        last->unknown08 = unknown10[i];
      }
      unknown48 = unknown18[i];
    }
  }
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
