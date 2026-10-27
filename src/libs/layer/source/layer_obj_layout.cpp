#include "layer/layer_obj_layout.h"

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_sort_man.h"
#include "mtl/alloc_handle.h"

namespace layer {

void LayerObjLayout::workLayoutRelease() {
  if (unknown2d0 != nullptr) {
    delete unknown2d0;
    unknown2d0 = nullptr;
  }
  if (unknown310[0].unknown18 != nullptr) {
    delete unknown310[0].unknown18;
    unknown310[0].unknown18 = nullptr;
  }
  if (unknown310[1].unknown18 != nullptr) {
    delete unknown310[1].unknown18;
    unknown310[1].unknown18 = nullptr;
  }
  if (unknown380.unknown18 != nullptr) {
    delete unknown380.unknown18;
    unknown380.unknown18 = nullptr;
  }
  if (unknown3b8.unknown18 != nullptr) {
    delete unknown3b8.unknown18;
    unknown3b8.unknown18 = nullptr;
  }
  if (unknown310[0].unknown20 != nullptr) {
    delete unknown310[0].unknown20;
    unknown310[0].unknown20 = nullptr;
  }
  if (unknown310[1].unknown20 != nullptr) {
    delete unknown310[1].unknown20;
    unknown310[1].unknown20 = nullptr;
  }
  if (unknown380.unknown20 != nullptr) {
    delete unknown380.unknown20;
    unknown380.unknown20 = nullptr;
  }
  if (unknown3b8.unknown20 != nullptr) {
    delete unknown3b8.unknown20;
    unknown3b8.unknown20 = nullptr;
  }
  if (unknown3f0 != nullptr) {
    delete unknown3f0;
    unknown3f0 = nullptr;
  }
  if (unknown3f8 != nullptr) {
    delete unknown3f8;
    unknown3f8 = nullptr;
  }
}

void LayerObjLayout::createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor) {
  unknown001 &target = unknown310[LayerManager::s_nStkIdx];
  target.unknown00 = 0x9;
  target.unknown04 = x;
  target.unknown08 = y;
  target.unknown0c = width;
  target.unknown10 = height;
  target.unknown28 = clearColor;
  unknown310[LayerManager::s_nStkIdx].unknown18 = new (LayerManager::get()->unknown28) grlib::CGLibRenderTarget();
}

void LayerObjLayout::releaseRenderTarget() {
  if (unknown3b8.unknown00 & 0x4) {
    unknown3b8.unknown00 |= 0x20 << LayerManager::s_nStkIdx;
  }
}

grlib::CGLibTextureBuffer *LayerObjLayout::getTexture() {
  if (unknown3b8.unknown00 & 0x4) {
    return unknown3b8.unknown18->unknown70;
  }

  s64 index = LayerManager::s_nStkIdx;
  if (!(unknown310[index].unknown00 & 0x1)) {
    index = LayerManager::s_nDebIdx;
    if (!(unknown310[index].unknown00 & 0x1)) {
      return nullptr;
    }
  }
  return unknown310[index].unknown18->unknown70;
}

void LayerObjLayout::setRender(bool render) {
  if (unknown3b8.unknown00 & 0x4) {
    if (render) {
      unknown3b8.unknown00 |= 0x8;
    } else {
      unknown3b8.unknown00 &= ~0x8;
    }
    return;
  }

  unknown001 *target = &unknown310[LayerManager::s_nStkIdx];
  u32 flags = target->unknown00;
  if (!(flags & 0x1)) {
    target = &unknown310[LayerManager::s_nDebIdx];
    flags = target->unknown00;
    if (!(flags & 0x1)) {
      return;
    }
  }

  if (render) {
    target->unknown00 = flags | 0x8;
  } else {
    target->unknown00 = flags & ~0x8;
  }
}

bool LayerObjLayout::isRender() const {
  u32 flags = unknown3b8.unknown00;
  if (!(flags & 0x4)) {
    flags = unknown310[LayerManager::s_nStkIdx].unknown00;
    if (!(flags & 0x1)) {
      flags = unknown310[LayerManager::s_nDebIdx].unknown00;
      if (!(flags & 0x1)) {
        return false;
      }
    }
  }
  return (flags >> 3) & 0x1;
}

} // namespace layer
