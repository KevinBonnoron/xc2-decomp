#include "layer/layer_obj_top_mem_obj.h"

#include <string.h>

#include "layer/layer_manager.h"

namespace layer {

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

} // namespace layer
