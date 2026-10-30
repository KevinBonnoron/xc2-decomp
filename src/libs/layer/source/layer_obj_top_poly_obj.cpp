#include "layer/layer_obj_top_poly_obj.h"

#include <string.h>

#include "grlib/cglib_ctl_vertex.h"
#include "grlib/cglib_texture_buffer.h"
#include "grlib/cglib_vtx_index.h"
#include "grlib/cglib_vtx_vertex.h"
#include "layer/layer_acc_poly_obj.h"
#include "layer/layer_link_list.h"
#include "layer/layer_manager.h"
#include "layer/layer_res_add_tex_obj.h"
#include "layer/layer_shd_manager.h"
#include "mtl/mem_manager.h"

namespace layer {

LayerObjTopPolyObj::~LayerObjTopPolyObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopPolyObj::releasePoly(layPolyWork &work) {
  if (work.unknown00[0] != nullptr) {
    delete work.unknown00[0];
    work.unknown00[0] = nullptr;
  }
  if (work.unknown00[1] != nullptr) {
    delete work.unknown00[1];
    work.unknown00[1] = nullptr;
  }
  if (work.unknown10[0] != nullptr) {
    delete work.unknown10[0];
    work.unknown10[0] = nullptr;
  }
  if (work.unknown10[1] != nullptr) {
    delete work.unknown10[1];
    work.unknown10[1] = nullptr;
  }
}

void LayerObjTopPolyObj::releaseWorkBuffer() {
  unknown280.release();
  releasePoly(unknown300);
  unknown2b8.clear();
  if (unknown368 != nullptr) {
    mtl::MemManager::deallocate(unknown368, 0, false);
    unknown368 = nullptr;
  }
}

void LayerObjTopPolyObj::createWorkBuffer(u32 width, u32 height) {
  unknown280.setup(0x60);
  f32 sclY = static_cast<f32>(height) / static_cast<f32>(width);
  unknown188 = 1.0f;
  unknown18c = sclY;
  f32 sclX = 1.0f;
  if (width <= height) {
    sclY = 1.0f;
    sclX = static_cast<f32>(width) / static_cast<f32>(height);
  }
  unknown180 = sclX;
  unknown184 = sclY;
  unknown190 = 0;
  unknown192 = 0;
  unknown194 = width;
  unknown196 = height;
  memset(&unknown300, 0, sizeof(unknown300));
}

void LayerObjTopPolyObj::updateVertexBuffer() {
  void *buffer;
  u32 size;
  if (unknown250 & (4 << LayerManager::s_nDebIdx)) {
    unknown250 &= ~(4 << LayerManager::s_nDebIdx);
    unknown250 |= 1;
    unknown300.unknown50 = (unknown300.unknown50 == 0);
    unknown300.unknown00[unknown300.unknown50]->lock(&buffer, &size);
    memcpy(buffer, unknown300.unknown20[LayerManager::s_nDebIdx], size);
    unknown300.unknown00[unknown300.unknown50]->unlock();
  }
  if (unknown250 & (0x10 << LayerManager::s_nDebIdx)) {
    unknown250 &= ~(0x10 << LayerManager::s_nDebIdx);
    unknown250 |= 2;
    unknown300.unknown52 = (unknown300.unknown52 == 0);
    unknown300.unknown10[unknown300.unknown52]->lock(&buffer, &size);
    memcpy(buffer, unknown300.unknown30[LayerManager::s_nDebIdx], size);
    unknown300.unknown10[unknown300.unknown52]->unlock();
  }
  if (unknown250 & (0x40 << LayerManager::s_nDebIdx)) {
    unknown250 &= ~(0x40 << LayerManager::s_nDebIdx);
    unknown300.unknown4c = unknown300.unknown44[LayerManager::s_nDebIdx];
    unknown300.unknown4e = unknown300.unknown48[LayerManager::s_nDebIdx];
  }
  unknown2b8.updateTexutre(nullptr, nullptr);
  grlib::CGLibTextureBuffer *texture = nullptr;
  if (unknown2b8.unknown00.unknown00 != nullptr) {
    texture = unknown2b8.unknown00.unknown00->getTexObj(0);
  }
  unknown278 = texture;
}

void LayerObjTopPolyObj::applyPartsSetup() { updateVertexBuffer(); }

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

void LayerObjTopPolyObj::finalRender() {
  LayerShdManager *shader = LayerManager::get()->unknown58;
  if (!shader->unknown002(unknown248, unknown258)) {
    return;
  }
  shader->unknown003(LayerShdManager::s_resDefBlend[unknownc5]);
  shader->unknown004(this);
  if (unknown278 != nullptr && unknown278->isInitialized()) {
    shader->unknown4f8 = 2;
  } else {
    shader->unknown4f8 = 1;
  }
  shader->setSecTexture(unknown220[2]);
  grlib::CGLibCtlVertex::setVertex(*unknown300.unknown00[unknown300.unknown50]);
  shader->unknown4f0 = 6;
  shader->setupShader(&unknown280);
  if (unknown278 != nullptr && unknown278->isInitialized()) {
    shader->setupTexture(*unknown278, static_cast<LayerSamplerType>(unknownc6), 0);
  }
  unknown300.unknown10[unknown300.unknown52]->drawIndex(unknown300.unknown4e, unknown300.unknown4c * 2);
}

} // namespace layer
