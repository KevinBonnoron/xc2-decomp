#include "layer/layer_obj_top_poly_obj.h"

#include "layer/layer_acc_poly_obj.h"
#include "layer/layer_manager.h"

namespace layer {

void LayerObjTopPolyObj::LockVertex() { unknown358 = unknown300.unknown20[LayerManager::s_nStkIdx]; }

void LayerObjTopPolyObj::setVertex(u32 index, const LayerPolyVertex &vertex) { static_cast<LayerPolyVertex *>(unknown358)[index] = vertex; }

void LayerObjTopPolyObj::UnlockVertex() {
  unknown250 |= 4 << LayerManager::s_nStkIdx;
  unknown358 = nullptr;
}

void LayerObjTopPolyObj::LockIndex() { unknown358 = unknown300.unknown30[LayerManager::s_nStkIdx]; }

void LayerObjTopPolyObj::setIndex(u32 index, u16 vertexIndex) { static_cast<u16 *>(unknown358)[index] = vertexIndex; }

void LayerObjTopPolyObj::UnlockIndex() {
  unknown250 |= 0x10 << LayerManager::s_nStkIdx;
  unknown358 = nullptr;
}

void LayerObjTopPolyObj::setTexutre(const void *data) { unknown2b8.setAddTexture(data, 0); }

void LayerObjTopPolyObj::setTexutre(grlib::CGLibTextureBuffer &texture) { unknown2b8.setAddTexture(texture, 0); }

void LayerObjTopPolyObj::resetTexutre() { unknown2b8.resetAddAllTexutre(); }

void LayerObjTopPolyObj::setIndexInfo(u16 start, u16 num) {
  s32 index = LayerManager::s_nStkIdx;
  unknown250 |= 0x40 << index;
  unknown300.unknown44[index] = start;
  unknown300.unknown48[index] = num;
}

} // namespace layer
