#include "layer/layer_sort_man.h"

#include <math.h>
#include <string.h>

#include "layer/layer_manager.h"
#include "layer/layer_sort_obj.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerSortMan::LayerSortMan(LayerManager *manager, u32 num2D, u32 num3D) {
  unknown60 = 255.0f;
  unknown64 = 300.0f;
  unknown68 = 0.8f;
  unknown6c = num2D;
  m_layerManager = manager;
  unknown08 = nullptr;
  unknown70 = num3D;

  u32 bits2D = num2D / 32 * 4 + 1;
  u32 bits3D = num3D / 32 * 4 + 1;
  unknown74 = bits2D + (32 - bits2D % 32) % 32;
  unknown78 = bits3D + (32 - bits3D % 32) % 32;
  s32 objSize = (unknown6c + unknown70) * 16;
  objSize += (32 - objSize % 32) % 32;
  s32 size = unknown74 + unknown78 + objSize;
  size += (32 - size % 32) % 32;
  u8 *buffer = static_cast<u8 *>(mtl::MemManager::allocate(manager->unknown28, size, 0x20, false, "no name", 0));
  unknown08 = buffer;

  unknown10 = reinterpret_cast<LayerSortObj **>(buffer);
  unknown18 = reinterpret_cast<LayerSortObj **>(buffer + unknown6c * sizeof(LayerSortObj *));
  s32 offset = unknown6c * 16;
  unknown20 = reinterpret_cast<LayerSortObj **>(buffer + offset);
  unknown28 = reinterpret_cast<LayerSortObj **>(buffer + (offset + unknown70 * sizeof(LayerSortObj *)));
  offset += unknown70 * 16;
  offset += (32 - offset % 32) % 32;
  unknown30 = reinterpret_cast<u32 *>(buffer + offset);
  offset += unknown74;
  unknown38 = reinterpret_cast<u32 *>(buffer + offset);
}

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
    unknown18[index]->m_layerSortObj = object;
  }
  object->m_layerSortObj = nullptr;
  unknown18[index] = object;
}

void LayerSortMan::set3DSpace(LayerSortObj *object, f32 depth) {
  f32 ratio = depth / unknown64;
  if (ratio >= 1.0f) {
    stock3DObj(object, unknown70 - 1);
  } else if (ratio <= 0.001f) {
    stock3DObj(object, 0);
  } else {
    ratio = powf(ratio, unknown68);
    s32 index = static_cast<s32>((1.0f - ratio) * unknown70);
    if (index >= static_cast<s32>(unknown70)) {
      index = unknown70 - 1;
    } else if (index < 0) {
      index = 0;
    }
    stock3DObj(object, index);
  }
}

void LayerSortMan::stock3DObj(LayerSortObj *object, s32 index) {
  u32 flags = unknown38[index >> 5];
  u32 mask = 1 << (index & 0x1f);
  if (!(flags & mask)) {
    unknown38[index >> 5] = flags | mask;
    unknown20[index] = object;
  } else {
    unknown28[index]->m_layerSortObj = object;
  }
  object->m_layerSortObj = nullptr;
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
        last->m_layerSortObj = unknown20[i];
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
        last->m_layerSortObj = unknown10[i];
      }
      unknown48 = unknown18[i];
    }
  }
}

void LayerSortMan::alphaRender() {
  for (LayerSortObj *object = unknown40; object != nullptr; object = object->m_layerSortObj) {
    object->alphaRender();
  }
}

void LayerSortMan::lastRender() {
  for (LayerSortObj *object = unknown40; object != nullptr; object = object->m_layerSortObj) {
    object->lastRender();
  }
}

void LayerSortMan::finalRender() {
  for (LayerSortObj *object = unknown40; object != nullptr; object = object->m_layerSortObj) {
    object->finalRender();
  }
}

} // namespace layer
