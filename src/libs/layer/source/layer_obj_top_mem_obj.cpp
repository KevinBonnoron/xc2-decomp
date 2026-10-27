#include "layer/layer_obj_top_mem_obj.h"

#include <string.h>

#include "grlib/cglib_texture_buffer.h"
#include "layer/layer_manager.h"
#include "mm_math/mm_col4.h"

namespace layer {

LayerObjTopMemObj::~LayerObjTopMemObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopMemObj::releaseWorkBuffer() {
  unknown278.release();
  unknown640.release();
  unknown678.release();
  unknown6a0[0].release();
  unknown6a0[1].release();
  unknown6f0[0].release();
  unknown6f0[1].release();
}

void LayerObjTopMemObj::resourceInit() {
  if (unknown270 & 0x8) {
    unknown270 &= ~0x8;
    unknown278.setTextureInfo(unknown740, unknown744, GRL_SURFACE_FORMAT_RGBA8, false, 0);
    unknown278.clearTexture(mm::Col4(0.0f, 0.0f, 0.0f, 0.0f), static_cast<GrlClaerMask>(0xf));
    u32 *info = static_cast<u32 *>(unknown678.m_mapping);
    info[0] = unknown740;
    info[1] = unknown744;
    if (unknown750 == LAYER_MEM_TYPE_UNKNOWN_3) {
      info[2] = unknown740 >> 1;
      info[3] = unknown744 >> 1;
    } else {
      info[2] = unknown740;
      info[3] = unknown744;
    }
    unknown678.updateData();
  }
}

void *LayerObjTopMemObj::getBuffer() { return unknown6a0[static_cast<u32>(LayerManager::s_nDebIdx)].m_mapping; }

void LayerObjTopMemObj::updateBufer() {
  u32 index = LayerManager::s_nDebIdx;
  memset(unknown6f0[index].m_mapping, 0, 0x10);
  unknown6f0[index].updateData();
  unknown6a0[index].updateData();
}

void LayerObjTopMemObj::setRender(bool render) {
  if (render) {
    unknown270 |= 0x4;
  } else {
    unknown270 &= ~0x4;
  }
}

bool LayerObjTopMemObj::isRender() const { return (unknown270 >> 2) & 0x1; }

void LayerObjTopMemObj::finalRender() {
  setupRender();
  if (isRender()) {
    lastRender();
  }
}

} // namespace layer
