#include "layer/layer_obj_top_mask_obj.h"

#include "layer/layer_base.h"
#include "layer/layer_manager.h"
#include "layer/layer_obj_util.h"
#include "layer/layer_shd_manager.h"
#include "layer/layer_texture_obj.h"

namespace layer {

namespace {

struct unknown010 {
  u8 _00[0x08];
  u8 unknown08; // Inferred role: flags; original member name unknown.
  u8 _09[0x0c - 0x09];
  u32 unknown0c; // Inferred role: offset of the layout info; original member name unknown.
  u8 _10[0x24 - 0x10];
  u32 unknown24; // Inferred role: offset of the texture; original member name unknown.
  u8 _28[0x2c - 0x28];
  u32 unknown2c; // Inferred role: offset of the icon info; original member name unknown.
};

struct unknown011 {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: width; original member name unknown.
  u8 _08[0x0c - 0x08];
  u32 unknown0c; // Inferred role: height; original member name unknown.
  f32 unknown10; // Inferred role: scale x; original member name unknown.
  f32 unknown14; // Inferred role: scale y; original member name unknown.
};

struct unknown012 {
  u32 unknown00; // Inferred role: icon max; original member name unknown.
};

} // namespace

LayerObjTopMaskObj::LayerObjTopMaskObj(const void *data) {
  unknown18 = LAYER_OBJ_TYPE_MASK;
  unknowna8 |= 0x20000;
  m_layerResViewPortInfo = nullptr;
  unknown238 = nullptr;
  createWorkBuffer(data);
}

LayerObjTopMaskObj::~LayerObjTopMaskObj() {
  baseRelease();
  releaseWorkBuffer();
}

void LayerObjTopMaskObj::createWorkBuffer(const void *data) {
  m_resData = data;
  const unknown010 *header = static_cast<const unknown010 *>(data);
  if (header->unknown24 != 0) {
    m_layerTextureObj = LayerManager::get()->m_layerShdManager->m_layerTextureMan->createTextureObj(static_cast<const u8 *>(data) + header->unknown24);
  }
  if (header->unknown08 & 0x2) {
    unknown2d2 = reinterpret_cast<const unknown012 *>(static_cast<const u8 *>(m_resData) + header->unknown2c)->unknown00;
  } else {
    unknown2d2 = 0;
  }
  unknown2d0 = 0;
  m_cGLibDblUniformBlock.setup(0x50);
  const unknown011 *info = reinterpret_cast<const unknown011 *>(static_cast<const u8 *>(m_resData) + header->unknown0c);
  m_layerResRenderInfo.unknown00 = info->unknown10;
  m_layerResRenderInfo.unknown04 = info->unknown14;
  m_layerResRenderInfo.unknown08 = 1.0f;
  m_layerResRenderInfo.unknown0c = static_cast<f32>(info->unknown0c) / static_cast<f32>(info->unknown04);
  m_layerResRenderInfo.m_pixelX = 0;
  m_layerResRenderInfo.m_pixelY = 0;
  m_layerResRenderInfo.m_pixelWidth = info->unknown04;
  m_layerResRenderInfo.m_pixelHeight = info->unknown0c;
}

void LayerObjTopMaskObj::releaseWorkBuffer() {
  m_cGLibDblUniformBlock.release();
  if (m_layerTextureObj != nullptr) {
    m_layerTextureObj->release();
    m_layerTextureObj = nullptr;
  }
}

const grlib::CGLibTextureBuffer &LayerObjTopMaskObj::getTexture() const { return *m_layerTextureObj->getTexture(0); }

void LayerObjTopMaskObj::resourceInit() {
  if (m_layerTextureObj != nullptr) {
    m_layerTextureObj->setupResource();
  }
}

void LayerObjTopMaskObj::setDrawList(LayerSortMan *sortMan, bool is3D) {}

} // namespace layer
