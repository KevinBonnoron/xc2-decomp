#include "layer/layer_obj_layout.h"

#include <string.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_top_tex_obj.h"
#include "layer/layer_sort_man.h"
#include "mtl/alloc_handle.h"

namespace layer {

LayerObjLayout::LayerObjLayout() {
  memset(&unknown2a0, 0, sizeof(unknown2a0));
  unknown2a0.unknown18 = 1.0f;
  unknown2a0.unknown1c = 1.0f;
  unknown2a0.unknown20 = 0;
  unknown3f8 = nullptr;
  unknown3f0 = nullptr;
}

void LayerObjLayout::workLayoutRelease() {
  if (unknown2a0.unknown30 != nullptr) {
    delete unknown2a0.unknown30;
    unknown2a0.unknown30 = nullptr;
  }
  if (unknown2a0.unknown70[0].unknown18 != nullptr) {
    delete unknown2a0.unknown70[0].unknown18;
    unknown2a0.unknown70[0].unknown18 = nullptr;
  }
  if (unknown2a0.unknown70[1].unknown18 != nullptr) {
    delete unknown2a0.unknown70[1].unknown18;
    unknown2a0.unknown70[1].unknown18 = nullptr;
  }
  if (unknown2a0.unknowne0.unknown18 != nullptr) {
    delete unknown2a0.unknowne0.unknown18;
    unknown2a0.unknowne0.unknown18 = nullptr;
  }
  if (unknown2a0.unknown118.unknown18 != nullptr) {
    delete unknown2a0.unknown118.unknown18;
    unknown2a0.unknown118.unknown18 = nullptr;
  }
  if (unknown2a0.unknown70[0].unknown20 != nullptr) {
    delete unknown2a0.unknown70[0].unknown20;
    unknown2a0.unknown70[0].unknown20 = nullptr;
  }
  if (unknown2a0.unknown70[1].unknown20 != nullptr) {
    delete unknown2a0.unknown70[1].unknown20;
    unknown2a0.unknown70[1].unknown20 = nullptr;
  }
  if (unknown2a0.unknowne0.unknown20 != nullptr) {
    delete unknown2a0.unknowne0.unknown20;
    unknown2a0.unknowne0.unknown20 = nullptr;
  }
  if (unknown2a0.unknown118.unknown20 != nullptr) {
    delete unknown2a0.unknown118.unknown20;
    unknown2a0.unknown118.unknown20 = nullptr;
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
  unknown001 &target = unknown2a0.unknown70[LayerManager::s_nStkIdx];
  target.unknown00 = 0x9;
  target.unknown04 = x;
  target.unknown08 = y;
  target.unknown0c = width;
  target.unknown10 = height;
  target.unknown28 = clearColor;
  unknown2a0.unknown70[LayerManager::s_nStkIdx].unknown18 = new (LayerManager::get()->unknown28) grlib::CGLibRenderTarget();
}

void LayerObjLayout::releaseRenderTarget() {
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    unknown2a0.unknown118.unknown00 |= 0x20 << LayerManager::s_nStkIdx;
  }
}

grlib::CGLibTextureBuffer *LayerObjLayout::getTexture() {
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    return unknown2a0.unknown118.unknown18->unknown70;
  }

  s64 index = LayerManager::s_nStkIdx;
  if (!(unknown2a0.unknown70[index].unknown00 & 0x1)) {
    index = LayerManager::s_nDebIdx;
    if (!(unknown2a0.unknown70[index].unknown00 & 0x1)) {
      return nullptr;
    }
  }
  return unknown2a0.unknown70[index].unknown18->unknown70;
}

void LayerObjLayout::setRender(bool render) {
  if (unknown2a0.unknown118.unknown00 & 0x4) {
    if (render) {
      unknown2a0.unknown118.unknown00 |= 0x8;
    } else {
      unknown2a0.unknown118.unknown00 &= ~0x8;
    }
    return;
  }

  unknown001 *target = &unknown2a0.unknown70[LayerManager::s_nStkIdx];
  u32 flags = target->unknown00;
  if (!(flags & 0x1)) {
    target = &unknown2a0.unknown70[LayerManager::s_nDebIdx];
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
  u32 flags = unknown2a0.unknown118.unknown00;
  if (!(flags & 0x4)) {
    flags = unknown2a0.unknown70[LayerManager::s_nStkIdx].unknown00;
    if (!(flags & 0x1)) {
      flags = unknown2a0.unknown70[LayerManager::s_nDebIdx].unknown00;
      if (!(flags & 0x1)) {
        return false;
      }
    }
  }
  return (flags >> 3) & 0x1;
}

} // namespace layer
